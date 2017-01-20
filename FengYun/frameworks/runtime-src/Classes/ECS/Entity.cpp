/**
 * @file  Entity.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Entity.h"

BEGIN_NS_ECS

Entity::Entity()
    : _id(0)
    , _active(true)
    , _activeInHierarchy(false)
    , _name("")
    , _transform(nullptr)
    , _world(nullptr)
{}

Entity::~Entity()
{}

void Entity::reset()
{
    _id = 0;
    _active = true;
    _activeInHierarchy = true;
    _name = "";
    _transform = nullptr;
    _world = nullptr;
}

void* Entity::getWorldUserData() const
{
    return _world->getUserData<void>();
}

void Entity::markGlobal()
{
    _world->markGlobalEntity(_id);
}

void Entity::setActive(bool value)
{
    if (_active == value) return;

    _active = value;

    auto& parent = _transform->getParent();
    if (parent && !parent->getEntity()->isActiveInHierarchy()) return;

    if (value)
        _world->addEntityActiveCommand(_id);
    else
        _world->addEntityInactiveCommand(_id);
}

const ComponentHandle<Transform>& Entity::getTransform() const
{
    if (!_transform)
        _transform = getComponent<Transform>();
    return _transform;
}

ComponentHandle<Component> Entity::addComponent(const ComponentType<Component>& t)
{
    int id, version;
    _world->allocComponent(t, &id, &version);
    ComponentHandle<Component> c(id, version);
    _components.insert(c);
    __component_internal::set(c.get(), id, EntityHandle(this));
    _world->addComponentAwakeCommand(id);
    return c;
}

void Entity::removeComponent(const ComponentHandle<Component>& c)
{
    _components.erase(c);
}

ComponentHandle<Component> Entity::getComponent(const ComponentType<Component>& t) const
{
    for (auto& c: _components)
    {
        if (t.isBaseOf(c->getType())) return c;
    }
    return ComponentHandle<Component>();
}

void Entity::getComponents(const ComponentType<Component>& t, std::vector<ComponentHandle<Component> >& v) const
{
    for (auto& c: _components)
    {
        if (t.isBaseOf(c->getType()))
            v.push_back(c);
    }
}

void Entity::onParentChanged(const ComponentHandle<Transform>& old, const ComponentHandle<Transform>& cur)
{
    if (!isActive()) return;

    bool oldActive = old ? old->getEntity()->isActiveInHierarchy() : true;
    bool curActive = cur ? cur->getEntity()->isActiveInHierarchy() : true;
    if (curActive != oldActive)
    {
        if (curActive)
            _world->addEntityActiveCommand(_id);
        else
            _world->addEntityInactiveCommand(_id);
    }
}

END_NS_ECS
