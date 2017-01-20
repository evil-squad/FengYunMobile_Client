/**
 * @file  World.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_WORLD_H
#define ECS_WORLD_H

#include "ecsbase.h"
#include "Event.h"
#include <memory>
#include <functional>

BEGIN_NS_ECS

template <class T>
class ComponentType;

class Entity;
class Component;

class EntityHandle
{
public:
    EntityHandle() : _id(0), _version(0) {}

    EntityHandle(std::nullptr_t) : _id(0), _version(0) {}

    EntityHandle(int id, int version) : _id(id), _version(version) {}

    EntityHandle(Entity* e);

    EntityHandle& operator= (std::nullptr_t);

    EntityHandle(const EntityHandle& o);

    EntityHandle& operator= (const EntityHandle& o);

    operator bool() { return valid(); }

    Entity& operator* () const;

    Entity* operator-> () const;

    bool valid() const;

    void destroy() const;

    bool operator== (const EntityHandle& o) const;

    bool operator!= (const EntityHandle& o) const;

    bool operator< (const EntityHandle& o) const;

    Entity* get() const { return get_ptr(); }

private:
    int _id;
    int _version;

    Entity* get_ptr() const;

    friend struct __handle_internal;
};

class BaseComponentHandle
{
public:
    inline operator bool() { return valid(); }

    bool valid() const;

    void destroy() const;

protected:
    BaseComponentHandle(Component* c);

    BaseComponentHandle(int id, int version) : _id(id), _version(version) {}

    BaseComponentHandle(const BaseComponentHandle& o) : _id(o._id), _version(o._version) {}

    int _id;
    int _version;

    Component* get_ptr() const;

    void assign(const BaseComponentHandle& o);

    bool equals(const BaseComponentHandle& o) const;

    bool less(const BaseComponentHandle& o) const;

    friend struct __handle_internal;
};

template <class T>
class ComponentHandle : public BaseComponentHandle
{
public:
    ComponentHandle() : BaseComponentHandle(0 ,0) {}

    ComponentHandle(Component* c) : BaseComponentHandle(c) {}

    ComponentHandle(int id, int version) : BaseComponentHandle(id, version) {}

    ComponentHandle(std::nullptr_t) : BaseComponentHandle(0, 0) {}

    ComponentHandle& operator= (std::nullptr_t);

    template <class Y, typename std::enable_if<std::is_convertible<Y*, T*>::value, T>::type* = nullptr>
    ComponentHandle(const ComponentHandle<Y>& o) : BaseComponentHandle(o) {}

    template <class Y, typename std::enable_if<std::is_convertible<Y*, T*>::value, T>::type* = nullptr>
    ComponentHandle& operator= (const ComponentHandle<Y>& o)
    {
        assign(o);
        return *this;
    }

    T* get() const { return static_cast<T*>(get_ptr()); }

    operator bool() const { return valid(); }

    T& operator* () const;

    T* operator-> () const;

    bool operator== (const ComponentHandle& o) const { return equals(o); }

    bool operator!= (const ComponentHandle& o) const { return !(*this == o); }

    bool operator< (const ComponentHandle& o) const { return less(o); }

};

class World
{
public:
    static World* getInstance();
    void destroyInstance();

    EntityHandle createEntity();

    EntityHandle findEntity(const std::string& name) const;

    void subscribeEvent(int id, const ComponentHandle<Component>& h);
    void unsubscribeEvent(int id, const ComponentHandle<Component>& h);

    void emitEvent(const Event<void>& ev);

    void setComponentPriority(const ComponentType<Component>& type, int priority);
    void resetComponentPriority();

    bool isRunning() const;

    void start();
    void update(float dt);
    void stop();

    void clear();
    void clearAll();

    template<class T>
    T* getUserData() const { return static_cast<T*>(_userData); }
    template<class T>
    void setUserData(T* data) { _userData = data; }

private:
    EntityHandle findEntityInChildren(const Entity* e, const std::string& name) const;

    int getFreeEntity();
    int getFreeComponent();

    void getHandle(Entity* e, int* id, int* version);
    void getHandle(Component* c, int* id, int* version);

    Entity* getEntity(int id);

    Component* getComponent(int id);

    bool checkEntity(int id, int version);
    bool checkComponent(int id, int version);

    void destroyEntity(int id);
    void destroyComponent(int id);

    void addRootEntity(int id);
    void removeRootEntity(int id);

    void allocComponent(const ComponentType<Component>& t, int* id, int* version);

    void markGlobalEntity(int id);

    void addComponentAwakeCommand(int id);
    void addComponentEnableCommand(int id);
    void addComponentDisableCommand(int id);
    void addComponentUpdateCommand(int id);

    void addEntityActiveCommand(int id);
    void addEntityInactiveCommand(int id);

    void addEntityDestroyCommand(int id);
    void addComponentDestroyCommand(int id);

    void addEntityReleaseCommand(int id);
    void addComponentReleaseCommand(int id);

    void addAwakeCommands();
    void addDestroyCommands();

    struct Command;
    void processCommands(float dt);
    void processCommand(const Command& command, float dt);

private:
    World();
    ~World();

    void* _userData;

    static World* _instance;

    struct WorldInternalData;
    WorldInternalData* _data;

    friend class Entity;
    friend class Component;
    friend class Transform;
    friend class EntityHandle;
    friend class BaseComponentHandle;
};

struct __handle_internal
{
    static int id(const EntityHandle& h) { return h._id; }
    static int version(const EntityHandle& h) { return h._version; }

    static int id(const BaseComponentHandle& h) { return h._id; }
    static int version(const BaseComponentHandle& h) { return h._version; }
};

inline EntityHandle::EntityHandle(Entity* e)
{
    World::getInstance()->getHandle(e, &_id, &_version);
}

inline EntityHandle& EntityHandle::operator=(std::nullptr_t)
{
    _id = 0;
    _version = 0;
    return *this;
}

inline EntityHandle::EntityHandle(const EntityHandle& o)
{
    *this = o;
}

inline EntityHandle& EntityHandle::operator=(const EntityHandle& o)
{
    _id = o._id;
    _version = o._version;
    return *this;
}

inline Entity& EntityHandle::operator*() const
{
    if (valid()) return *get();
    throw std::bad_cast();
}

inline Entity* EntityHandle::operator->() const
{
    if (valid()) return get();
    throw std::bad_cast();
}

inline bool EntityHandle::valid() const
{
    if (_id == 0) return false;
    return World::getInstance()->checkEntity(_id, _version);
}

inline void EntityHandle::destroy() const
{
    if (valid())
        World::getInstance()->destroyEntity(_id);
}

inline bool EntityHandle::operator==(const fy::ecs::EntityHandle &o) const
{
    return _id == o._id && _version == o._version;
}

inline bool EntityHandle::operator!=(const fy::ecs::EntityHandle &o) const
{
    return !(*this == o);
}

inline bool EntityHandle::operator<(const fy::ecs::EntityHandle &o) const
{
    if (_id == o._id) return _version < o._version;
    return _id < o._id;
}

inline Entity* EntityHandle::get_ptr() const
{
    return World::getInstance()->getEntity(_id);
}

inline bool BaseComponentHandle::valid() const
{
    if (_id == 0) return false;
    return World::getInstance()->checkComponent(_id, _version);
}

inline void BaseComponentHandle::destroy() const
{
    if (valid())
        World::getInstance()->destroyComponent(_id);
}

inline BaseComponentHandle::BaseComponentHandle(Component* c)
{
    World::getInstance()->getHandle(c, &_id, &_version);
}

inline Component* BaseComponentHandle::get_ptr() const
{
    return World::getInstance()->getComponent(_id);
}

inline void BaseComponentHandle::assign(const fy::ecs::BaseComponentHandle &o)
{
    _id = o._id;
    _version = o._version;
}

inline bool BaseComponentHandle::equals(const fy::ecs::BaseComponentHandle &o) const
{
    return _id == o._id && _version == o._version;
}

inline bool BaseComponentHandle::less(const fy::ecs::BaseComponentHandle &o) const
{
    if (_id == o._id) return _version < o._version;
    return _id < o._id;
}

template <class T>
inline ComponentHandle<T>& ComponentHandle<T>::operator=(std::nullptr_t)
{
    _id = 0;
    _version = 0;
    return *this;
}

template <class T>
inline T& ComponentHandle<T>::operator*() const
{
    if (valid()) return *get();
    throw std::bad_cast();
}

template <class T>
inline T* ComponentHandle<T>::operator->() const
{
    if (valid()) return get();
    throw std::bad_cast();
}

template <class T, class Y>
ComponentHandle<T> component_cast(const ComponentHandle<Y>& o)
{
    return ComponentHandle<T>(__handle_internal::id(o), __handle_internal::version(o));
}
END_NS_ECS

namespace std
{
    template<>
    struct hash<fy::ecs::EntityHandle>
    {
        typedef fy::ecs::EntityHandle argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& v) const
        {
            int id = fy::ecs::__handle_internal::id(v);
            int version = fy::ecs::__handle_internal::version(v);
            result_type const h1 (std::hash<int>()(id));
            result_type const h2 (std::hash<int>()(version));
            return h1 ^ (h2 << 1);
        }
    };

    template<class T>
    struct hash<fy::ecs::ComponentHandle<T> >
    {
        typedef fy::ecs::ComponentHandle<T> argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& v) const
        {
            int id = fy::ecs::__handle_internal::id(v);
            int version = fy::ecs::__handle_internal::version(v);
            result_type const h1 (std::hash<int>()(id));
            result_type const h2 (std::hash<int>()(version));
            return h1 ^ (h2 << 1);
        }
    };
}

#endif /* ECS_WORLD_H */
