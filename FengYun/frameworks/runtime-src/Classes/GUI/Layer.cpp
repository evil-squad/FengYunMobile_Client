/**
 * @file  Layer.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Layer.h"
#include "DebugHelper.h"

namespace gui
{
    Layer* Layer::create()
    {
        Layer* layer = new Layer();
        if (layer && layer->init())
        {
            layer->autorelease();
            return layer;
        }
        CC_SAFE_DELETE(layer);
        return nullptr;
    }

    Layer::Layer()
    {
    }

    Layer::~Layer()
    {
    }

    bool Layer::init()
    {
        return cocos2d::Layer::init();
    }

    void Layer::addChild(cocos2d::Node *child)
    {
        cocos2d::Node::addChild(child);
    }

    void Layer::addChild(cocos2d::Node *child, int zOrder)
    {
        cocos2d::Node::addChild(child, zOrder);
    }

    void Layer::addChild(cocos2d::Node *child, int zOrder, int tag)
    {
        DBG_ASSERT(dynamic_cast<TopLevelNode*>(child) != nullptr,
                   "gui Layer only supports gui TopLevelNode objects  as children!");

        cocos2d::Node::addChild(child, zOrder, tag);
    }

    void Layer::addChild(cocos2d::Node *child, int zOrder, const std::string &name)
    {
        DBG_ASSERT(dynamic_cast<TopLevelNode*>(child) != nullptr,
                   "gui Layer only supports gui TopLevelNode objects as children!");

        cocos2d::Node::addChild(child, zOrder, name);
    }

    void Layer::removeChild(cocos2d::Node *child, bool cleanup)
    {
        DBG_ASSERT(dynamic_cast<TopLevelNode*>(child) != nullptr,
                   "gui Layer only supports gui TopLevelNode objects as children!");

        cocos2d::Node::removeChild(child, cleanup);
    }

    void Layer::closeAll()
    {
        auto children = _children;
        for (auto& child: children)
        {
            static_cast<TopLevelNode*>(child)->close(false);
        }
        removeAllChildren();
    }
}
