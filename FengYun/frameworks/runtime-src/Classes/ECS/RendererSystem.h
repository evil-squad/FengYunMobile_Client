/**
 * @file  RendererSystem.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_RENDERERSYSTEM_H
#define ECS_RENDERERSYSTEM_H

#include "Component.h"
#include "Renderer.h"

BEGIN_NS_ECS

class RendererSystem : public Component
{
public:
    RendererSystem();
    virtual ~RendererSystem();

    cocos2d::Node* getLayer() { return _layer; }

protected:
    void onAwake() override;
    void onDestroy() override;

    void onReceive(const Event<void>& ev) override;

private:
    cocos2d::Node* _layer;
};

template <>
class component_traits<RendererSystem>
{
public:
    typedef Component parent_type;
    static const char* name() { return "RendererSystem"; }
    static int flags() { return ComponentFlags::HAS_RECEIVE_MESSAGE; }
    static Component* create() { return new RendererSystem(); }
};

END_NS_ECS
#endif /* ECS_RENDERERSYSTEM_H */
