/**
 * @file  NetRole.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "NetRole.h"
#include "DebugHelper.h"

USING_NS_CC;
BEGIN_NS_ECS

static const float ANGLE_OFFSET = 22.5;
static const float PLAYER_RUN_SPEED = 100;

namespace
{
static std::pair<std::string, bool> getFaceName(FaceDir dir)
{
    switch (dir)
    {
        case FaceDir::FRONT:
            return std::make_pair("front", false);
        case FaceDir::BACK:
            return std::make_pair("back", false);
        case FaceDir::RIGHT:
            return std::make_pair("right", false);
        case FaceDir::LEFT:
            return std::make_pair("right", true);
        case FaceDir::RIGHT_DOWN:
            return std::make_pair("rightdown", false);
        case FaceDir::LEFT_DOWN:
            return std::make_pair("rightdown", true);
        case FaceDir::RIGHT_UP:
            return std::make_pair("rightup", false);
        case FaceDir::LEFT_UP:
            return std::make_pair("rightup", true);
        default:
            break;
    }
    return std::make_pair("front", false);
}

FaceDir changeFaceDir(float angle)
{
    if (angle <= -90 + ANGLE_OFFSET && angle > -90 - ANGLE_OFFSET)
        return FaceDir::FRONT;
    else if (angle <= -45 + ANGLE_OFFSET && angle > -45 - ANGLE_OFFSET)
        return FaceDir::RIGHT_DOWN;
    else if ( angle <= 0 + ANGLE_OFFSET && angle > 0 - ANGLE_OFFSET)
        return FaceDir::RIGHT;
    else if (angle <= 45 + ANGLE_OFFSET && angle > 45 - ANGLE_OFFSET)
        return FaceDir::RIGHT_UP;
    else if (angle <= 90 + ANGLE_OFFSET && angle > 90 - ANGLE_OFFSET)
        return FaceDir::BACK;
    else if (angle <= 135 + ANGLE_OFFSET && angle > 135 - ANGLE_OFFSET)
        return FaceDir::LEFT_UP;
    else if ((angle <= 180 && angle > 180 - ANGLE_OFFSET) || (angle <= -180 + ANGLE_OFFSET && angle > -180))
        return FaceDir::LEFT;
    else if (angle <= -135 + ANGLE_OFFSET && angle > -135 - ANGLE_OFFSET)
        return FaceDir::LEFT_DOWN;

    return FaceDir::NONE;
}

static void createAnimation(const std::string& path, const std::string& name, cocos2d::Map<std::string, cocos2d::Animation*>& animations)
{
    auto an = cocos2d::Animation::create();
    for (int i = 1; i < 100; ++i)
    {
        char szName[100] = {0};
        sprintf(szName, "man_%s_%02d.png", name.c_str(), i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
        if (!frame)
            break;

        an->addSpriteFrame(frame);
    }

    an->setDelayPerUnit(2.8f / 14.0f);
    an->setRestoreOriginalFrame(true);

    animations.insert(name, an);
}
}

NetRole* NetRole::create()
{
    auto r = new NetRole();
    if (r && r->init())
    {
        r->autorelease();
        return r;
    }
    CC_SAFE_DELETE(r);
    return nullptr;
}

NetRole::NetRole()
    :_faceDir(FaceDir::NONE)
    , _skin(nullptr)
    , _nameLabel(nullptr)
{}

NetRole::~NetRole()
{}

bool NetRole::init()
{
    if (!Node::init()) return false;
    for (int i = (int)FaceDir::FRONT; i <= (int)FaceDir::LEFT_DOWN; ++ i)
    {
        char szName[64] = {0};
        std::pair<std::string, bool> info = getFaceName((fy::FaceDir)i);
        sprintf(szName, "stand_%s", info.first.c_str());
        createAnimation("stand", szName, _animations);

        char szName1[64] = {0};
        sprintf(szName1, "run_%s", info.first.c_str());
        createAnimation("run", szName1, _animations);
    }
    _skin = Sprite::create();
    _skin->setPosition(Vec2::ZERO);
    _skin->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _skin->setContentSize(Size(10, 10));
    this->addChild(_skin);

    this->setContentSize(Size(10, 10));
    return true;
}

void NetRole::setFaceDir(fy::FaceDir value)
{
    if (_faceDir == value) return;

    _faceDir = value;
    auto iter = getFaceName(value);

    this->playAnimation("stand");
}

void NetRole::onStart()
{
    DBG_DRAW(_skin, Color4F(0, 1, 0, 0.5));
    DBG_DRAW(this, Color4F(1, 0, 0, 0.5));

    this->setFaceDir(fy::FaceDir::FRONT);
}

void NetRole::onMove(const cocos2d::Vec2 &endPos, const std::function<void ()> &cb)
{
    this->stopAllActions();
    auto curPos = this->getPosition();
    float dis = curPos.getDistance(endPos);
    this->playAnimation("run");
    auto move = MoveTo::create(dis / PLAYER_RUN_SPEED, endPos);
    auto call = CallFunc::create([=]{
        this->playAnimation("stand");

        if (cb) cb();
    });
    auto seq = Sequence::create(move, call, NULL);
    this->runAction(seq);
}

void NetRole::checkAngle(float angle)
{
    FaceDir face = changeFaceDir(angle);
    this->setFaceDir(face);
}

void NetRole::playAnimation(const std::string& state)
{
    _skin->stopAllActions();
    auto iter = getFaceName(_faceDir);
    std::string str = StringUtils::format("%s_%s", state.c_str(), iter.first.c_str());
    auto action = _animations.at(str);
    if (action)
    {
        auto ac = Animate::create(action);
        auto rep = RepeatForever::create(ac);
        _skin->runAction(rep);
        _skin->setFlippedX(iter.second);
    }
}

END_NS_ECS
