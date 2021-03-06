/**
 * @file  UIScene.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UIScene.h"
#include "UIManager.h"
#include "GameModule.h"

BEGIN_NS_SCENES

UIScene* UIScene::create(const std::string& name, const std::function<void()>& enterCb)
{
    UIScene* s = new UIScene();

    if (s && s->init(name, enterCb))
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

UIScene::UIScene()
 : _uiLayer(nullptr)
 , _enterCb(nullptr)
{}

UIScene::~UIScene()
{}

bool UIScene::init(const std::string &name, const std::function<void ()> &enterCb)
{
    this->setName(name);
    _enterCb = enterCb;

    _uiLayer = gui::Layer::create();
    this->addChild(_uiLayer);

    return true;
}

void UIScene::onEnter()
{
    cocos2d::Scene::onEnter();
    GameModule::get<UIManager>()->registerUILayer(_uiLayer);
    if (_enterCb) _enterCb();
}

void UIScene::onExit()
{
    _uiLayer->closeAll();
    GameModule::get<UIManager>()->unregisterUILayer(_uiLayer);
    cocos2d::Scene::onExit();
}

END_NS_SCENES
