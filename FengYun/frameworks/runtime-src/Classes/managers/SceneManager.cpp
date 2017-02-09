/**
 * @file  SceneManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "SceneManager.h"

#include <algorithm>

#include "Scenes/UIScene.h"
#include "Scenes/CityController.h"
#include "GameApp.h"

USING_NS_CC;
using namespace std;

BEGIN_NS_FY

USING_NS_SCENES;

struct SceneManager::PrivateData
{
    GameScene* current;

    PrivateData()
        : current(nullptr)
    {

    }
    ~PrivateData()
    {

    }
};

SceneManager::SceneManager()
{
    _data = new PrivateData();
}

SceneManager::~SceneManager()
{
    delete _data;
}

void SceneManager::onInitialize()
{

}

void SceneManager::onRelease()
{

}

GameScene* SceneManager::getCurrent()
{
    return _data->current;
}

void SceneManager::gotoUIScene(const std::string &name, const std::function<void ()> &enterCb)
{
    auto s = UIScene::create(name, [this, enterCb]{
        if (_data->current)
        {
            _data->current->release();
            _data->current = nullptr;
        }
        if (enterCb) enterCb();
    });
    Director::getInstance()->replaceScene(s);
}

void SceneManager::gotoScene(int id)
{
    auto scene = GameScene::create(id);
    _data->current = scene;
    scene->setController(new CityController(scene));
    _data->current->retain();
    scene->onSceneBegin();
    auto size = Director::getInstance()->getVisibleSize();
    scene->getController()->onSetPlayerAgent(1000, Vector3(size.width / 2, size.height / 2, 0), fy::FaceDir::FRONT, nullptr);
    Director::getInstance()->replaceScene(scene);
}

END_NS_FY
