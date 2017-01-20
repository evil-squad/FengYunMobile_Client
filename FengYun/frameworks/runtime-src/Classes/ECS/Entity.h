/**
 * @file  Entity.h
* @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H

#include "ecsbase.h"
#include "Transform.h"
#include "World.h"
#include <set>
#include <vector>
#include <string>

BEGIN_NS_ECS

class Entity
{
public:
    typedef std::set<ComponentHandle<Component> >::const_iterator const_iterator;

    Entity();
    ~Entity();

    void markGlobal();

    bool isActive() const { return _active; }
    bool isActiveInHierarchy() const { return _activeInHierarchy; }
    void setActive(bool value);

    const std::string& getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    World* getWorld() { return _world; }
    const World* getWorld() const { return _world; }

    template<class T>
    T* getWorldUserData() const { return static_cast<T*>(getWorldUserData()); }

    template<class T>
    ComponentHandle<T> addComponent()
    {
        return component_cast<T>(addComponent(component_type<T>()));
    }

    template<class T>
    ComponentHandle<T> getComponent() const
    {
        return component_cast<T>(getComponent(component_type<T>()));
    }

    template<class T>
    std::vector<ComponentHandle<T> > getComponents() const
    {
        return component_vector_cast<T>(getComponents(component_type<T>()));
    }

    const ComponentHandle<Transform>& getTransform() const;

    void emitEvent(const Event<void>& ev)
    {
        for (auto& c: _components)
        {
            c->emitEvent(ev);
        }
    }

    std::size_t getComponentCount() const { return _components.size(); }

    const_iterator begin() const { return _components.begin(); }
    const_iterator end() const { return _components.end(); }

private:
    void reset();

    void* getWorldUserData() const;

private:
    int _id;
    bool _active;
    bool _activeInHierarchy;
    std::string _name;
    World* _world;
    mutable ComponentHandle<Transform> _transform;
    std::set<ComponentHandle<Component> > _components;
    ComponentHandle<Component> addComponent(const ComponentType<Component>& c);
    void removeComponent(const ComponentHandle<Component>& c);

    ComponentHandle<Component> getComponent(const ComponentType<Component>& c) const;
    std::vector<ComponentHandle<Component> > getComponents(const ComponentType<Component>& t) const
    {
        std::vector<ComponentHandle<Component> > v;
        getComponents(t, v);
        return v;
    }

    void getComponents(const ComponentType<Component>& t, std::vector<ComponentHandle<Component> >& v) const;

    template<class T>
    static std::vector<ComponentHandle<T> > component_vector_cast(const std::vector<ComponentHandle<Component> >& v)
    {
        std::vector<ComponentHandle<T> > ret;
        ret.resize(v.size());
        for (std::size_t i = 0; i < v.size(); ++ i)
        {
            ret[i] = component_cast<T>(v[i]);
        }
        return ret;
    }

    void onParentChanged(const ComponentHandle<Transform>& old, const ComponentHandle<Transform>& cur);

    friend struct __entity_internal;
};

struct __entity_internal
{
    static int id(Entity* e) { return e->_id; }

    static void set(Entity* e, int id, World* w)
    {
        e->_id = id;
        e->_world = w;
    }

    static void on_parent_change(
        Entity* e,
        const ComponentHandle<Transform>& old,
        const ComponentHandle<Transform>& cur)
    {
        e->onParentChanged(old, cur);
    }

    static void set_active_in_hierarchy(Entity* e, bool value)
    {
        e->_activeInHierarchy = value;
    }

    static void remove_component(Entity* e, const ComponentHandle<Component>& c)
    {
        e->removeComponent(c);
    }

    static void reset(Entity* e)
    {
        e->reset();
    }
};

END_NS_ECS
#endif /* ECS_ENTITY_H */









