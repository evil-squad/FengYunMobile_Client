/**
 * @file  DebugHelper.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "cocos2d.h"

class DebugHelper
{
public:
    static void debugBreak()
    {
        int i = 0;
        i ++;
    }

static void debugDraw(cocos2d::Node* node, cocos2d::Color4F color = cocos2d::Color4F(0, 1, 0, 0.5))
{
    auto drawNode = cocos2d::DrawNode::create();
    auto size = node->getContentSize();
    cocos2d::Vec2 poses[] = { cocos2d::Vec2(0, 0), cocos2d::Vec2(size.width, 0),cocos2d::Vec2(size.width, size.height), cocos2d::Vec2(0, size.height) };
    drawNode->drawSolidPoly(poses, 4, color);
    drawNode->setPosition(cocos2d::Vec2(0, 0));
    node->addChild(drawNode, 100);
}
};

#define DBG_DRAW(node, color) DebugHelper::debugDraw(node, color)

#define ENABLE_DEBUG_LOG

#define ENABLE_DEBUG_FPS

#define DBG_ASSERT(cond, msg) CCASSERT(cond, msg)

#ifdef ENABLE_DEBUG_LOG
#define DBG_LOG(...) CCLOG(__VA_ARGS__)
#else
#define DBG_LOG(...)
#endif

#endif /* DEBUGHELPER_H */
