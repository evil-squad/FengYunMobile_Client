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

USING_NS_CC;
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
    , _player(nullptr)
{}

GameScene::~GameScene()
{}

bool GameScene::initWithId(int id)
{
    if (!cocos2d::Scene::init()) return false;

    _id = id;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("avatar/man/man_stand.plist", "avatar/man/man_stand.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("avatar/man/man_run.plist", "avatar/man/man_run.png");

    _sceneNode = cocos2d::Node::create();
    this->addChild(_sceneNode);

    _uiLayer = gui::Layer::create();
    this->addChild(_uiLayer);

    _player = ecs::NetRole::create();

    this->initMap();

    _sceneNode->setContentSize(cocos2d::Size(3000, 3000));

    _player->setPosition(Vec2(200, 200));
    _player->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _sceneNode->addChild(_player);

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

    this->initMapTouch();

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
    listener->onTouchBegan = ([=] (Touch* touch, Event* event){
        auto target = event->getCurrentTarget();
        auto pos = touch->getLocation();
        auto loc = target->convertToNodeSpace(pos);
        auto playerPos = _player->getPosition();
        auto dis = loc - playerPos;

        _player->checkAngle(dis.getAngle() * 180/M_PI);

        _player->onMove(loc, nullptr);

        return true;
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _sceneNode);
}

void GameScene::onEnter()
{
    cocos2d::Scene::onEnter();
    _player->onStart();

    GameModule::get<UIManager>()->registerUILayer(_uiLayer);

    this->adjustVirePoint(-1);

    this->scheduleUpdate();
}

void GameScene::onExit()
{
    _uiLayer->closeAll();
    GameModule::get<UIManager>()->unregisterUILayer(_uiLayer);

    this->unscheduleUpdate();

    cocos2d::Scene::onExit();
}

void GameScene::update(float dt)
{
    this->adjustVirePoint(dt);
}

void GameScene::setViewPoint(const Vector2 &pos)
{
    if (_viewPoint != pos)
    {
        _viewPoint = pos;
        updateView();
    }
}

void GameScene::adjustVirePoint(float dt)
{
    const Size& size = Director::getInstance()->getVisibleSize();
    const Size& mapSize = _sceneNode->getContentSize();

    auto playerPos = _player->getPosition();

    auto pos = _player->getPosition() - Vector2(size.width * 0.5, size.height * 0.5);
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
    DBG_LOG("update view point ========>%f, %f", pos.x, pos.y);
    _sceneNode->setPosition(pos);
}

END_NS_SCENES
