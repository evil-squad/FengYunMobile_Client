/**
 * @file  WorldEvent.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_WORLDEVENT_H
#define ECS_WORLDEVENT_H

#include "ecsbase.h"
#include "World.h"

BEGIN_NS_ECS

class EntityAddedEvent : public Event<EntityAddedEvent>
{
public:
    static const char* getTypeName() { return "EntityAddedEvent"; }

    EntityAddedEvent(const EntityHandle& e)
    : entity(e)
    {}

    EntityHandle entity;
};

class EntityRemovedEvent : public Event<EntityRemovedEvent>
{
public:
    static const char* getTypeName() { return "EntittRemovedEvent"; }

    EntityRemovedEvent(const EntityHandle& e)
    : entity(e)
    {}

    EntityHandle entity;
};

class ComponentAddedEvent : public Event<ComponentAddedEvent>
{
public:
    static const char* getTypeName() { return "ComponentAddedEvent"; }

    ComponentAddedEvent(const ComponentHandle<Component>& c)
    : component(c)
    {}

    ComponentHandle<Component> component;
};

class ComponentRemovedEvent : public Event<ComponentRemovedEvent>
{
public:
    static const char* getTypeName() { return "ComponentRemoveEvent"; }

    ComponentRemovedEvent(const ComponentHandle<Component>& c)
    : component(c)
    {}
    
    ComponentHandle<Component> component;
};

END_NS_ECS
#endif /* ECS_WORLDEVENT_H */
