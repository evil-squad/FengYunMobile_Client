/**
 * @file  World.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "World.h"
#include "WorldEvent.h"
#include "Entity.h"
#include "DebugHelper.h"

#include <set>
#include <map>
#include <queue>
#include <memory>
#include <unordered_set>

//#define ENABLE_ECS_LOG

BEGIN_NS_ECS

namespace {
    enum class CommandType
    {
        AWAKE_COMPONENT,
        ENABLE_COMPONENT,
        DISABLE_COMPONENT,
        UPDATE_COMPONENT,
        DESTROY_COMPONENT,
        RELEASE_ENTITY,
        RELEASE_COMPONENT
    };

    struct EntityRef
    {
        Entity entity;
        int version;

        EntityRef()
        : entity()
        , version(1)
        {}
    };

    struct ComponentRef
    {
        Component* component;
        int version;

        ComponentRef() : component(nullptr) , version(1) {}
    };

    struct ComponentGroup
    {
        int priority;
        std::unordered_set<int> components;
    };

    struct ComponentGroupLess
    {
        typedef ComponentGroup* value_type;
        bool operator()(const value_type& a, const value_type& b) const
        {
            return a->priority < b->priority;
        }
    };

    struct EventHandlerGroup
    {
        std::set<ComponentHandle<Component> > handlers;

        void operator()(const Event<void>& ev)
        {
            for (auto& h: handlers)
                h->emitEvent(ev);
        }
    };
}

World *World::_instance = nullptr;

struct World::Command
{
    CommandType type;
    int id;
    int version;

    Command(CommandType type_, int id_, int version_) : type(type_) , id(id_) , version(version_) {}
};

struct World::WorldInternalData
{
    bool running;

    std::set<int> globalEntities;
    std::set<int> rootEntities;
    std::set<int> awakeComponents;
    std::set<int> destroyEntities;
    std::set<int> destroyComponents;
    std::map<int, EventHandlerGroup> eventHandlers;
    std::vector<EntityRef> entityCache;
    std::vector<ComponentRef> componentCache;
    std::queue<int> freeEntities;
    std::queue<int> freeComponents;
    std::multiset<ComponentGroup*, ComponentGroupLess> componentGroups;
    std::map<const ComponentType<Component>*, std::unique_ptr<ComponentGroup> > componentGroupMap;
    std::queue<Command> commands;
};

World* World::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new World();
    }
    return _instance;
}

void World::destroyInstance()
{
    if (_instance != nullptr)
        delete _instance;
    _instance = nullptr;
}

World::World()
: _userData(nullptr)
{
    _data = new WorldInternalData();
    _data->running = false;
}

World::~World()
{
    clearAll();
    delete _data;
}

EntityHandle World::createEntity()
{
    int id = getFreeEntity();
#ifdef ENABLE_ECS_LOG
    DBG_LOG("create entity %d", id);
#endif
    auto& ref = _data->entityCache[id-1];
    __entity_internal::set(&ref.entity, id, this);
    if (_data->running)
        __entity_internal::set_active_in_hierarchy(&ref.entity, true);
    ref.entity.addComponent<Transform>();
    _data->rootEntities.insert(id);
    emitEvent(EntityAddedEvent(EntityHandle(id, ref.version)));
    return EntityHandle(id, ref.version);
}

EntityHandle World::findEntity(const std::string& name) const
{
    EntityHandle h;
    const Entity* e;
    for (int id: _data->rootEntities)
    {
        e = &_data->entityCache[id-1].entity;
        if (e->getName() == name) return EntityHandle(id, _data->entityCache[id-1].version);
        h = findEntityInChildren(e, name);
        if (h) return h;
    }
    return h;
}

EntityHandle World::findEntityInChildren(const Entity* e, const std::string& name) const
{
    EntityHandle h;
    Entity* c;
    for (auto& t: *e->getTransform())
    {
        c = t->getEntity().get();
        if (c->getName() == name) return t->getEntity();

        h = findEntityInChildren(c, name);
        if (h) return h;
    }
    return h;
}

void World::subscribeEvent(int id, const ComponentHandle<Component>& h)
{
    _data->eventHandlers[id].handlers.insert(h);
}

void World::unsubscribeEvent(int id, const ComponentHandle<Component>& h)
{
    auto& g = _data->eventHandlers[id];
    g.handlers.erase(h);
    if (g.handlers.empty())
        _data->eventHandlers.erase(id);
}

void World::emitEvent(const Event<void>& ev)
{
    auto it = _data->eventHandlers.find(ev.getId());
    if (it != _data->eventHandlers.end())
    {
        it->second(ev);
    }
}

void World::setComponentPriority(const ComponentType<Component>& type, int priority)
{
    if (!(type.getFlags() & ComponentFlags::HAS_UPDATE)) return;

    auto it = _data->componentGroupMap.find(&type);
    if (it == _data->componentGroupMap.end())
    {
        auto g = new ComponentGroup();
        g->priority = priority;
        _data->componentGroups.insert(g);
        _data->componentGroupMap[&type] = std::unique_ptr<ComponentGroup>(g);
    }
    else
    {
        auto g = it->second.get();
        _data->componentGroups.erase(g);
        g->priority = priority;
        _data->componentGroups.insert(g);
    }
}

void World::resetComponentPriority()
{
    _data->componentGroups.clear();
    for (auto& kvp: _data->componentGroupMap)
    {
        kvp.second->priority = 0;
        _data->componentGroups.insert(kvp.second.get());
    }
}

bool World::isRunning() const
{
    return _data->running;
}

void World::start()
{
    addAwakeCommands();
    addDestroyCommands();
    processCommands(0);

    _data->running = true;

    for (int id: _data->rootEntities)
    {
        if (_data->entityCache[id-1].entity.isActive())
            addEntityActiveCommand(id);
    }
    processCommands(0);
}

void World::update(float dt)
{
    DBG_ASSERT(_data->running, "Can not update world when world is not running!");

    addAwakeCommands();
    addDestroyCommands();
    processCommands(0);

    Component* c;

    for (auto g: _data->componentGroups)
    {
        for (auto id: g->components)
        {
            c = _data->componentCache[id-1].component;
            if (c->isEnabled() && c->getEntity()->isActiveInHierarchy())
                addComponentUpdateCommand(id);
        }
    }
    processCommands(dt);
}

void World::stop()
{
    addAwakeCommands();
    addDestroyCommands();
    processCommands(0);

    for (int id: _data->rootEntities)
    {
        if (_data->entityCache[id-1].entity.isActive())
            addEntityInactiveCommand(id);
    }
    processCommands(0);

    _data->running = false;
}

void World::clear()
{
    for (int id: _data->rootEntities)
    {
        if (_data->globalEntities.count(id) == 0)
            _data->destroyEntities.insert(id);
    }

    if (!_data->running)
    {
        addAwakeCommands();
        addDestroyCommands();
        processCommands(0);
    }
}

void World::clearAll()
{
    for (int id: _data->rootEntities)
    {
        _data->destroyEntities.insert(id);
    }

    if (!_data->running)
    {
        addAwakeCommands();
        addDestroyCommands();
        processCommands(0);
    }
}

int World::getFreeEntity()
{
    if (_data->freeEntities.empty())
    {
        int i = _data->entityCache.size();
        int c = 0;
        if (i == 0)
            c = 10;
        else
            c = i * 2;
        _data->entityCache.resize(c);
        ++i; ++c;
        for (; i<c; ++i)
            _data->freeEntities.push(i);
    }

    int id = _data->freeEntities.front();
    _data->freeEntities.pop();
    return id;
}

int World::getFreeComponent()
{
    if (_data->freeComponents.empty())
    {
        int i = _data->componentCache.size();
        int c = 0;
        if (i == 0)
            c = 20;
        else
            c = i * 2;
        _data->componentCache.resize(c);
        ++i; ++c;
        for (; i<c; ++i)
            _data->freeComponents.push(i);
    }

    int id = _data->freeComponents.front();
    _data->freeComponents.pop();
    return id;
}

void World::getHandle(Entity* e, int* id, int* version)
{
    int id_ = __entity_internal::id(e);
    *id = id_;
    *version = _data->entityCache[id_-1].version;
}

void World::getHandle(Component* c, int* id, int* version)
{
    int id_ = __component_internal::id(c);
    *id = id_;
    *version = _data->componentCache[id_-1].version;
}

Entity* World::getEntity(int id)
{
    return &_data->entityCache[id-1].entity;;
}

Component* World::getComponent(int id)
{
    return _data->componentCache[id-1].component;
}

bool World::checkEntity(int id, int version)
{
    return _data->entityCache[id-1].version == version;
}

bool World::checkComponent(int id, int version)
{
    return _data->componentCache[id-1].version == version;
}

void World::destroyEntity(int id)
{
    _data->destroyEntities.insert(id);
}

void World::destroyComponent(int id)
{
    auto& ref = _data->componentCache[id-1];
    if (ref.component->getType() == component_type<Transform>())
        destroyEntity(__handle_internal::id(ref.component->getEntity()));
    else
        _data->destroyComponents.insert(id);
}

void World::addRootEntity(int id)
{
    _data->rootEntities.insert(id);
}

void World::removeRootEntity(int id)
{
    _data->rootEntities.erase(id);
}

void World::allocComponent(const ComponentType<Component>& t, int* id, int* version)
{
    int id_ = getFreeComponent();
    auto& ref = _data->componentCache[id_-1];
    ref.component = t.create_component();
    *id = id_;
    *version = ref.version;
#ifdef ENABLE_ECS_LOG
    DBG_LOG("create component %d, type %s", id_, t.getName());
#endif
}

void World::markGlobalEntity(int id)
{
    _data->globalEntities.insert(id);
}

void World::addComponentAwakeCommand(int id)
{
    _data->awakeComponents.insert(id);
}

void World::addAwakeCommands()
{
    // FIXME: this has a bug for set enabled when awake, need use queue for fix it
    for (int id: _data->awakeComponents)
    {
        _data->commands.push(Command(CommandType::AWAKE_COMPONENT, id, _data->componentCache[id-1].version));
    }
    _data->awakeComponents.clear();
}

void World::addDestroyCommands()
{
    for (int id: _data->destroyEntities)
    {
        addEntityDestroyCommand(id);
    }

    for (int id: _data->destroyComponents)
    {
        addComponentDestroyCommand(id);
    }

    for (int id: _data->destroyComponents)
    {
        addComponentReleaseCommand(id);
    }

    for (int id: _data->destroyEntities)
    {
        addEntityReleaseCommand(id);
    }

    _data->destroyEntities.clear();
    _data->destroyComponents.clear();
}

void World::addComponentEnableCommand(int id)
{
    if (_data->awakeComponents.count(id) == 1) return;
    _data->commands.push(Command(CommandType::ENABLE_COMPONENT, id, _data->componentCache[id-1].version));
}

void World::addComponentDisableCommand(int id)
{
    if (_data->awakeComponents.count(id) == 1) return;
    _data->commands.push(Command(CommandType::DISABLE_COMPONENT, id, _data->componentCache[id-1].version));
}

void World::addComponentUpdateCommand(int id)
{
    _data->commands.push(Command(CommandType::UPDATE_COMPONENT, id, _data->componentCache[id-1].version));
}

void World::addEntityActiveCommand(int id)
{
    auto& ref = _data->entityCache[id-1];

    __entity_internal::set_active_in_hierarchy(&ref.entity, true);

    for (auto& c: ref.entity)
    {
        if (c->isEnabled())
            addComponentEnableCommand(__handle_internal::id(c));
    }

    for (auto& t: *ref.entity.getTransform())
    {
        auto& e = t->getEntity();
        if (e->isActive())
            addEntityActiveCommand(__handle_internal::id(e));
    }
}

void World::addEntityInactiveCommand(int id)
{
    auto& ref = _data->entityCache[id-1];

    __entity_internal::set_active_in_hierarchy(&ref.entity, false);

    for (auto& c: ref.entity)
    {
        if (c->isEnabled())
            addComponentDisableCommand(__handle_internal::id(c));
    }

    for (auto& t: *ref.entity.getTransform())
    {
        auto& e = t->getEntity();
        if (e->isActive())
            addEntityInactiveCommand(__handle_internal::id(e));
    }
}

void World::addEntityDestroyCommand(int id)
{
    auto& ref = _data->entityCache[id-1];

    for (auto& t: *ref.entity.getTransform())
    {
        addEntityDestroyCommand(__entity_internal::id(t->getEntity().get()));
    }

    for (auto& c: ref.entity)
    {
        addComponentDestroyCommand(__component_internal::id(c.get()));
    }
}

void World::addComponentDestroyCommand(int id)
{
    auto& ref = _data->componentCache[id-1];

    _data->commands.push(Command(CommandType::DESTROY_COMPONENT, id, ref.version));
}

void World::addEntityReleaseCommand(int id)
{
    auto& ref = _data->entityCache[id-1];

    for (auto& c: ref.entity)
    {
        addComponentReleaseCommand(__component_internal::id(c.get()));
    }

    for (auto& t: *ref.entity.getTransform())
    {
        addEntityReleaseCommand(__entity_internal::id(t->getEntity().get()));
    }

    _data->commands.push(Command(CommandType::RELEASE_ENTITY, id, ref.version));
}

void World::addComponentReleaseCommand(int id)
{
    auto& ref = _data->componentCache[id-1];

    _data->commands.push(Command(CommandType::RELEASE_COMPONENT, id, ref.version));
}

void World::processCommands(float dt)
{
    while (!_data->commands.empty())
    {
        processCommand(_data->commands.front(), dt);
        _data->commands.pop();
    }
}

void World::processCommand(const Command& c, float dt)
{
    switch (c.type)
    {
        case CommandType::AWAKE_COMPONENT:
            if (checkComponent(c.id, c.version))
            {
                auto& ref = _data->componentCache[c.id-1];
                //DBG_LOG("awake component %d", c.id);
                __component_internal::on_awake(ref.component);
                if (_data->running && ref.component->isEnabled() && ref.component->getEntity()->isActiveInHierarchy())
                {
                    //DBG_LOG("enable component %d", c.id);
                    __component_internal::on_enable(ref.component);
                }

                auto& type = ref.component->getType();
                if (type.getFlags() & ComponentFlags::HAS_UPDATE)
                {
                    ComponentGroup* g = nullptr;
                    auto it = _data->componentGroupMap.find(&type);
                    if (it == _data->componentGroupMap.end())
                    {
                        g = new ComponentGroup();
                        _data->componentGroups.insert(g);
                        _data->componentGroupMap[&type] = std::unique_ptr<ComponentGroup>(g);
                    }
                    else
                    {
                        g = it->second.get();
                    }
                    g->components.insert(c.id);
                }

                emitEvent(ComponentAddedEvent(ComponentHandle<Component>(c.id, ref.version)));
            }
            break;
        case CommandType::ENABLE_COMPONENT:
            if (checkComponent(c.id, c.version))
            {
                //DBG_LOG("enable component %d", c.id);
                __component_internal::on_enable(_data->componentCache[c.id-1].component);
            }
            break;
        case CommandType::DISABLE_COMPONENT:
            if (checkComponent(c.id, c.version))
            {
                //DBG_LOG("disable component %d", c.id);
                __component_internal::on_disable(_data->componentCache[c.id-1].component);
            }
            break;
        case CommandType::UPDATE_COMPONENT:
            if (checkComponent(c.id, c.version))
                _data->componentCache[c.id-1].component->update(dt);
            break;
        case CommandType::DESTROY_COMPONENT:
            if (checkComponent(c.id, c.version))
            {
                auto& ref = _data->componentCache[c.id-1];
                emitEvent(ComponentRemovedEvent(ComponentHandle<Component>(c.id, ref.version)));
                if (_data->running && ref.component->isEnabled() && ref.component->getEntity()->isActiveInHierarchy())
                {
                    //DBG_LOG("disable component %d", c.id);
                    __component_internal::on_disable(ref.component);
                }
                //DBG_LOG("destroy component %d", c.id);
                __component_internal::on_destroy(ref.component);

                auto& type = ref.component->getType();
                if (type.getFlags() & ComponentFlags::HAS_UPDATE)
                {
                    _data->componentGroupMap[&type]->components.erase(c.id);
                }
            }
            break;
        case CommandType::RELEASE_ENTITY:
            if (checkEntity(c.id, c.version))
            {
                auto& ref = _data->entityCache[c.id-1];
                emitEvent(EntityRemovedEvent(EntityHandle(c.id, ref.version)));
#ifdef ENABLE_ECS_LOG
                DBG_LOG("release entity %d, name %s", c.id, ref.entity.getName().c_str());
#endif
                DBG_ASSERT(ref.entity.getComponentCount() == 0, "Has rest Component!");
                _data->globalEntities.erase(c.id);
                __entity_internal::reset(&ref.entity);
                ref.version++;
                _data->freeEntities.push(c.id);
            }
            break;
        case CommandType::RELEASE_COMPONENT:
            if (checkComponent(c.id, c.version))
            {
                auto& ref = _data->componentCache[c.id-1];
#ifdef ENABLE_ECS_LOG
                DBG_LOG("release component %d, type %s", c.id, ref.component->getType().getName());
#endif
                if (ref.component->getType() == component_type<Transform>())
                {
                    DBG_ASSERT(static_cast<Transform*>(ref.component)->getChildCount() == 0, "Has rest child!");
                }
                __entity_internal::remove_component(ref.component->getEntity().get(), ComponentHandle<Component>(c.id, c.version));
                delete ref.component;
                ref.component = nullptr;
                ref.version++;
                _data->freeComponents.push(c.id);
            }
            break;
        default:
            break;
    }
}

END_NS_ECS
