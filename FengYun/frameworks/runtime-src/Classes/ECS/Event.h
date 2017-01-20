/**
 * @file  Event.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_EVENT_H
#define ECS_EVENT_H

#include "ecsbase.h"
#include <memory>

BEGIN_NS_ECS

template <class T>
struct event_traits;

template <class T>
int event_id()
{
    return event_traits<T>::id();
}

class BaseEvent
{
public:
    virtual const char* getName() const = 0;

    int getId() const { return _id; }

protected:
    BaseEvent(int id)
        : _id(id)
    {}
private:
    int _id;
};

template <class T>
class Event;

template <>
class Event<void> : public BaseEvent
{
public:
    template<class Y>
    const Y& cast() const
    {
        if (getId() == event_id<Y>())
            return *static_cast<const Y*>(this);
        throw std::bad_cast();
    }

protected:
    Event(int id)
        : BaseEvent(id)
    {}
};

template <class T>
class Event : public Event<void>
{
public:
    Event(const Event& o) = delete;
    Event& operator= (const Event& o) = delete;

    virtual const char* getName() const { return event_traits<T>::name();  }

    const T& cast() const { return *static_cast<const T*>(this); }

protected:
    Event()
        : Event<void>(event_traits<T>::id())
    {}
};

template <>
struct event_traits<void>
{
protected:
    static int new_id()
    {
        static int counter = 0;
        return ++counter;
    }
};

template <class T>
class event_traits : event_traits<void>
{
public:
    static int id()
    {
        static int id = new_id();
        return id;
    }

    static const char* name() { return T::getTypeName(); }
};

END_NS_ECS
#endif /* ECS_EVENT_H */
