/**
 * @file  UIManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UIManager.h"
#include "DebugHelper.h"

USING_NS_CC;

BEGIN_NS_FY

UIManager::UIManager()
    : _uiRect(Rect::ZERO)
    , _uiLayer(nullptr)
{
}

UIManager::~UIManager()
{
    DBG_ASSERT(_uiLayer == nullptr, "UILayer not unregister!");
}

void UIManager::initUIRect()
{
    const cocos2d::Vec2& origin = Director::getInstance()->getVisibleOrigin();
    const cocos2d::Size& size = Director::getInstance()->getVisibleSize();
    _uiRect = Rect(origin.x, origin.y, size.width, size.height);
}

void UIManager::registerUILayer(gui::Layer *layer)
{
    DBG_ASSERT(_uiLayer == nullptr, "Already has UILayer");
    DBG_ASSERT(layer != nullptr, "Invalid UILayer");
    layer->retain();
    _uiLayer = layer;
}

void UIManager::unregisterUILayer(gui::Layer *layer)
{
    DBG_ASSERT(layer == _uiLayer, "UILayer not match!");
    _uiLayer->release();
    _uiLayer = nullptr;
}

END_NS_FY
