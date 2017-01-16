/**
 * @file  GameScene.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GameScene.h"
#include "GameModule.h"
#include "UIManager.h"

BEGIN_NS_SCENES

GameScene* GameScene::create(int id)
{
    auto s = new GameScene();
    if (s && s->initWithId(id))
    {
        s->autorelease();
        return s;
    }
    CC_SAFE_DELETE(s);
    return nullptr;
}

GameScene::GameScene()
    : _id(0)
{}

GameScene::~GameScene()
{}

bool GameScene::initWithId(int id)
{
    if (!cocos2d::Scene::init()) return false;

    _id = id;

    _sceneNode = cocos2d::Node::create();
    this->addChild(_sceneNode);

    _uiLayer = gui::Layer::create();
    this->addChild(_uiLayer);

    return true;
}

void GameScene::onEnter()
{
    cocos2d::Scene::onEnter();

    GameModule::get<UIManager>()->registerUILayer(_uiLayer);
}

void GameScene::onExit()
{
    _uiLayer->closeAll();
    GameModule::get<UIManager>()->unregisterUILayer(_uiLayer);

    cocos2d::Scene::onExit();
}

void GameScene::update(float dt)
{
    
}


END_NS_SCENES
