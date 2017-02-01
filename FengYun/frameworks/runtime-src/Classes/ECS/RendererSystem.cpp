/**
 * @file  RendererSystem.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "RendererSystem.h"
#include "Transform.h"
#include "Renderer.h"
#include "WorldEvent.h"
#include "Entity.h"
#include "World.h"

#include "cocos2d.h"
#include "SceneProjector.h"

#define MAX_LOCAL_Z 100000

BEGIN_NS_ECS

class ObjectLayer : public cocos2d::Node
{
};

RendererSystem::RendererSystem()
    : Component(component_type<RendererSystem>())
{
    _layer = ObjectLayer::create();
    _layer->retain();
}

RendererSystem::~RendererSystem()
{
    _layer->release();
}

void RendererSystem::onAwake()
{
    getWorld()->subscribeEvent(event_id<ComponentAddedEvent>(), ComponentHandle<RendererSystem>(this));
    getWorld()->subscribeEvent(event_id<ComponentRemovedEvent>(), ComponentHandle<RendererSystem>(this));
    getWorld()->subscribeEvent(event_id<TransformChangeEvent>(), ComponentHandle<RendererSystem>(this));
}

void RendererSystem::onDestroy()
{
    getWorld()->unsubscribeEvent(event_id<ComponentAddedEvent>(), ComponentHandle<RendererSystem>(this));
    getWorld()->unsubscribeEvent(event_id<ComponentRemovedEvent>(), ComponentHandle<RendererSystem>(this));
    getWorld()->unsubscribeEvent(event_id<TransformChangeEvent>(), ComponentHandle<RendererSystem>(this));
}

static void updateDisplayNode(const ComponentHandle<Transform>& trans, const ComponentHandle<Renderer>& ren)
{
    auto pos = trans->getWorldPosition();

    float depth = 0;
    int z = (int)((1 - depth) * MAX_LOCAL_Z);
    ren->getDisplayNode()->setLocalZOrder(z);

    auto p = SceneProjector::project(pos);
    ren->getDisplayNode()->setPosition(cocos2d::Vec2(p.x, p.y + p.z));
}

void RendererSystem::onReceive(const Event<void> &ev)
{
    if (ev.getId() == event_id<ComponentAddedEvent>())
    {
        auto& e = ev.cast<ComponentAddedEvent>();
        if (e.component->getType() == component_type<Renderer>())
        {
            auto ren = component_cast<Renderer>(e.component);
            _layer->addChild(ren->getDisplayNode());
            updateDisplayNode(e.component->getEntity()->getTransform(), ren);
        }
        return;
    }

    if (ev.getId() == event_id<ComponentRemovedEvent>())
    {
        auto& e = ev.cast<ComponentRemovedEvent>();
        if (e.component->getType() == component_type<Renderer>())
        {
            auto ren = component_cast<Renderer>(e.component);
            _layer->removeChild(ren->getDisplayNode());
        }
        return;
    }

    if (ev.getId() == event_id<TransformChangeEvent>())
    {
        auto& e = ev.cast<TransformChangeEvent>();
        auto ren = e.transform->getEntity()->getComponent<Renderer>();
        if (ren)
            updateDisplayNode(e.transform, ren);

        return;
    }
}

END_NS_ECS
