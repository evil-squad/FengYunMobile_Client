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
#include "DebugHelper.h"
#include "SceneProjector.h"
#include "SceneController.h"
#include "ECS/World.h"
#include "ECS/RendererSystem.h"
#include "ECS/Entity.h"
#include "ECS/NavAgent.h"
#include "ECS/Player.h"

USING_NS_CC;
USING_NS_ECS;
BEGIN_NS_SCENES

static const float CAMERA_FOLLOW_COEF = 1/ 90.0;

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
    , _viewPoint(Vector2::ZERO)
    , _uiLayer(nullptr)
    , _sceneNode(nullptr)
    , _controller(nullptr)
    , _time(0)
    , _battleController(nullptr)
    , _map(nullptr)
{

}

GameScene::~GameScene()
{
    onSceneEnd();
    ecs::World::getInstance()->clear();
    if (_controller)
    {
        delete _controller;
        _controller = nullptr;
    }

    if (_battleController)
    {
        delete _battleController;
        _controller = nullptr;
    }
}

bool GameScene::initWithId(int id)
{
    if (!cocos2d::Scene::init()) return false;

    _id = id;

    _sceneNode = cocos2d::Node::create();
    this->addChild(_sceneNode);

    _uiLayer = gui::Layer::create();
    this->addChild(_uiLayer);

    _map = GameModule::get<MapManager>()->createMap(id);

//    this->initMap();

//    _sceneNode->setContentSize(cocos2d::Size(3000, 3000));

    auto labelTip = Label::createWithSystemFont("点击屏幕控制角色行走", "Helvetica", 24);
    auto& rect = GameModule::get<UIManager>()->getUIRect();
    labelTip->setPosition(Vec2(rect.size.width * 0.5, rect.size.height - 4));
    labelTip->setAnchorPoint(Vec2(0.5, 1));
    labelTip->setColor(Color3B::RED);
    this->addChild(labelTip);
    auto s1 = ScaleTo::create(0.5, 1.2);
    auto s2 = ScaleTo::create(0.5, 1.0);
    auto seq = Sequence::create(s1, s2, NULL);
    auto rep = RepeatForever::create(seq);
    labelTip->runAction(rep);

//    this->initMapTouch();

    auto systemEntity = World::getInstance()->findEntity("RendererSystem");
    if (!systemEntity)
    {
        systemEntity = World::getInstance()->createEntity();
        systemEntity->setName("RendererSystem");
        systemEntity->markGlobal();
        systemEntity->addComponent<RendererSystem>();
        World::getInstance()->setComponentPriority(component_type<NavAgent>(), 1);
        //do not finish here
    }

    return true;
}

void GameScene::initMap()
{
    for (int i = 0; i < 3; ++ i)
    {
        for (int j = 0; j < 3; ++ j)
        {
            auto sprite = cocos2d::Sprite::create("maps/ditu2.png");
            sprite->setPosition(Vector2(1000 * i, 1000 * j));
            sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
            _sceneNode->addChild(sprite);
        }
    }
}

void GameScene::initMapTouch()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = ([=] (Touch* touch, cocos2d::Event* event){
        auto target = event->getCurrentTarget();
        auto pos = touch->getLocation();
        auto loc = target->convertToNodeSpace(pos);

        //        _player->checkAngle(dis.getAngle() * 180/M_PI);

        return true;
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _sceneNode);
}

void GameScene::onEnter()
{
    cocos2d::Scene::onEnter();

    GameModule::get<UIManager>()->registerUILayer(_uiLayer);

    _controller->onSceneEnter();

    auto p = ecs::Player::getCurrent()->getTransform()->getPosition();
    _map.adjust(Vec2(p.x, p.y));

    this->adjustViewPoint(-1);

    this->scheduleUpdate();
}

void GameScene::onExit()
{
    this->unscheduleUpdate();

    _uiLayer->closeAll();

    _controller->onSceneExit();

    GameModule::get<UIManager>()->unregisterUILayer(_uiLayer);

    cocos2d::Scene::onExit();
}

void GameScene::setController(SceneController *controller)
{
    DBG_ASSERT(_controller == nullptr, "Already has scene controller!");
    _controller = controller;
}

void GameScene::onSceneBegin()
{
    auto map = _map.getMapLayer();
    _sceneNode->addChild(map);
    map->setPosition(Vec2::ZERO);
    map->setAnchorPoint(Vec2::ZERO);

    GameModule::get<MapManager>()->registerMap(_map);

    auto rendererSystem = World::getInstance()->findEntity("RendererSystem")->getComponent<RendererSystem>();
    auto layer = rendererSystem->getLayer();
    layer->removeFromParent();
    _sceneNode->addChild(layer);

    ecs::World::getInstance()->setUserData<GameScene>(this);
    ecs::World::getInstance()->start();
}

void GameScene::onSceneEnd()
{
    GameModule::get<MapManager>()->unregisterMap(_map);
    World::getInstance()->stop();
    World::getInstance()->setUserData<GameScene>(nullptr);
}

void GameScene::update(float dt)
{
    _time += dt;
    
    _controller->onSceneUpdate(dt);

    ecs::World::getInstance()->update(dt);

    this->adjustViewPoint(dt);
}

void GameScene::setViewPoint(const Vector2 &pos)
{
    if (_viewPoint != pos)
    {
        _viewPoint = pos;
        updateView();
    }
}

void GameScene::adjustViewPoint(float dt)
{
    Viewer viewer;
    if (_viewer)
        viewer = _viewer;
    else
        viewer = ecs::Player::getCurrent();
    if (!viewer) return;

    const Size& size = Director::getInstance()->getVisibleSize();
    const Size& mapSize = _map.getSize();

    auto playerPos = viewer->getTransform()->getPosition();

    auto pos = worldToLayerPoint(playerPos) - Vector2(size.width * 0.5, size.height * 0.5);
    float scale = playerPos.y * 0.00005;
    float scaleOffsetX = scale * 500;

    float minX = 0;
    float minY = 0;
    float maxX = mapSize.width - scaleOffsetX;
    float maxY = mapSize.height - scaleOffsetX;

    if (pos.x < minX)
        pos.x = minX;
    else if (pos.x > (maxX - size.width))
        pos.x = maxX - size.width;

    if (pos.y < minY)
        pos.y = minY;
    else if (pos.y > (maxY - size.height ))
        pos.y = maxY - size.height;

    if (dt < 0)
    {
         setViewPoint(pos);
        return;
    }

    auto viewPt = getViewPoins();
    auto delta = pos - viewPt;
    auto lengSqr = delta.lengthSquared();

    if (lengSqr > 0)
    {
        float followSpeed = lengSqr * CAMERA_FOLLOW_COEF + 3;
        float deltaMove = followSpeed * dt;
        if (lengSqr >= deltaMove * deltaMove)
        {
            delta.normalize();
            delta.y *= 3.5;
            setViewPoint(viewPt + delta * deltaMove);
        }
        else
        {
            setViewPoint(pos);
        }
    }
}

void GameScene::updateView()
{
    auto pos = -_viewPoint;
    _sceneNode->setPosition(pos);
    _map.adjust(_viewPoint);
}

Vector2 GameScene::worldToLayerPoint(const Vector3 &pos) const
{
    auto p = SceneProjector::project(pos);
    return Vector2(p.x, p.y + p.z);
}

Vector2 GameScene::worldToUIPoint(const Vector3 &pos) const
{
    return worldToLayerPoint(pos) - _viewPoint;
}

Vector3 GameScene::uiToWorldPoint(const Vector2 &pos) const
{
    auto scenePos = _uiLayer->convertToNodeSpace(pos);
    auto worldPos = _sceneNode->convertToNodeSpace(scenePos);
    return Vector3(worldPos.x, worldPos.y, 0);
}

END_NS_SCENES
