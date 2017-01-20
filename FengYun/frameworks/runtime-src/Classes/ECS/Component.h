/**
 * @file  Component.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H

#include "ecsbase.h"
#include "World.h"

BEGIN_NS_ECS

template <class T>
class ComponentType;
template <class T>
class Event;

struct ComponentFlags
{
    enum
    {
        HAS_UPDATE = 0x01,
        HAS_RECEIVE_MESSAGE = 0x02
    };
};

class Component
{
public:
    virtual ~Component() {}

    const ComponentType<Component>& getType() const { return *_type; }
    const EntityHandle& getEntity() const { return _entity; }

    World* getWorld() const;

    template<class T>
    T* getWorldUserData() const { return static_cast<T*>(getWorldUserData()); }

    void setEnabled( bool value);
    bool isEnabled() const { return _enabled; }

    void update(float dt);

    void emitEvent(const Event<void>& ev);

protected:
    Component(const ComponentType<Component>& type)
    : _enabled(true)
    , _started(false)
    , _type(&type)
    , _id(0)
    , _entity(nullptr)
    {}

    void* getWorldUserData() const;

protected:
    virtual void onEnable() {}
    virtual void onDisable() {}

    virtual void onAwake() {}
    virtual void onStart() {}
    virtual void onDestroy() {}

    virtual void onUpdate(float dt) {}
    virtual void onReceive(const Event<void>& ev) {}

private:
    bool _enabled;
    bool _started;
    const ComponentType<Component>* _type;
    int _id;
    EntityHandle _entity;
    friend struct __component_internal;
};

struct __component_internal
{
    static int id(Component* c) { return c->_id; }
    static void set(Component* c, int id, const EntityHandle& e)
    {
        c->_id = id;
        c->_entity = e;
    }

    static void on_enable(Component* c)
    {
        c->onEnable();
    }

    static void on_disable(Component* c)
    {
        c->onDisable();
    }

    static void on_awake(Component* c)
    {
        c->onAwake();
    }

    static void on_destroy(Component* c)
    {
        c->onDestroy();
    }
};

class BaseComponentType
{
public:
    bool hasParentType() const { return _parent != nullptr; }
    const BaseComponentType& getParentType() const { return *_parent; }

    const char* getName() const { return _name; }

    int getFlags() const { return _flags; }

    bool isBaseOf(const BaseComponentType& o) const
    {
        const BaseComponentType* p = &o;
        while (true)
        {
            if (p == this) return true;
            if (!p->hasParentType()) break;
            p = &p->getParentType();
        }
        return false;
    }

    virtual Component* create_component() const = 0;
    virtual void release_component(Component* c) const = 0;

    bool operator== (const BaseComponentType& o) const
    {
        return this == &o;
    }

    bool operator!= (const BaseComponentType& o) const
    {
        return !(*this == o);
    }

    bool operator< (const BaseComponentType& o) const
    {
        return this < &o;
    }

protected:
    BaseComponentType(const BaseComponentType* parent, const char* name, int flags)
    : _parent(parent)
    , _name(name)
    , _flags(flags)
    {}

private:
    const BaseComponentType* _parent;
    const char* _name;
    int _flags;
};

template<class T>
struct component_traits {};

template<class T>
const ComponentType<T>& component_type();

template <>
class ComponentType<Component> : public BaseComponentType
{
public:
    static const ComponentType& getInstance()
    {
        static ComponentType instance;
        return instance;
    }

    virtual Component* create_component() const { return nullptr; }
    virtual void release_component(Component* c) const { delete c; }

protected:
    ComponentType()
        : BaseComponentType(nullptr, "Component", 0)
    {}

    ComponentType(const BaseComponentType& parent, const char* name, int flags)
    : BaseComponentType(&parent, name, flags)
    {}
};

template <class T>
class ComponentType : public ComponentType<Component>
{
public:
    static const ComponentType& getInstance()
    {
        static ComponentType instance;
        return instance;
    }

    virtual Component* create_component() const { return component_traits<T>::create(); }

private:
    typedef typename component_traits<T>::parent_type parent_type;

    ComponentType()
    : ComponentType<Component>(component_type<parent_type>(), component_traits<T>::name(), component_traits<T>::flags())
    {}
};

template <class T>
const ComponentType<T>& component_type()
{
    return ComponentType<T>::getInstance();
}

inline void Component::update(float dt)
{
    if (!_started)
    {
        _started = true;
        onStart();
    }

    onUpdate(dt);
}

inline void Component::emitEvent(const Event<void> &ev)
{
    if (getType().getFlags() & ComponentFlags::HAS_RECEIVE_MESSAGE)
        onReceive(ev);
}

END_NS_ECS
#endif /* ECS_COMPONENT_H */
