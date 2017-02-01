/**
 * @file  Renderer.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_RENDERER_H
#define ECS_RENDERER_H

#include "Component.h"

namespace cocos2d
{
    class Node;
    class Sprite;
}

BEGIN_NS_ECS

class Renderer : public Component
{
public:
    Renderer();
    virtual ~Renderer();

    cocos2d::Node* getDisplayNode() const { return _displayNode; }

protected:
    virtual void onEnable() override;
    virtual void onDisable() override;

private:
    cocos2d::Node* _displayNode;
};

template <>
class component_traits<Renderer>
{
public:
    typedef Component parent_type;
    static const char* name() { return "Renderer"; }
    static int flags() { return 0; }
    static Component* create() { return new Renderer(); }
};

END_NS_ECS
#endif /* ECS_RENDERER_H */
