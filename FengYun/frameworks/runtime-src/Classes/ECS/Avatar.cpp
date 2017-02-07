/**
 * @file  Avatar.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Avatar.h"
#include "cocos2d.h"
#include <memory>
#include "RoleTypes.h"
#include "Entity.h"
#include "Role.h"
#include "AnimationManager.h"
#include "GameModule.h"

USING_NS_CC;

BEGIN_NS_ECS

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

    void loadResources(const std::string& path, const std::string& name, const std::string& ext)
    {
        auto p = path + "/";
        char plistPath[128] = {0};
        sprintf(plistPath, "%s%s_%s.plist", p.c_str(), name.c_str(), ext.c_str());
        if (FileUtils::getInstance()->isFileExist(plistPath))
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath);
    }

    static void createAnimation(const std::string& name)
    {
        auto an = cocos2d::Animation::create();
        for (int i = 1; i < 100; ++i)
        {
            char szName[100] = {0};
            sprintf(szName, "%s_%02d.png", name.c_str(), i);
            auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(szName);
            if (!frame)
                break;

            an->addSpriteFrame(frame);
        }

        an->setDelayPerUnit(2.8f / 14.0f);
        an->setRestoreOriginalFrame(true);

        GameModule::get<AnimationManager>()->addAnimation(name, an);
    }
}

Avatar::Avatar()
    : Component(component_type<Avatar>())
    , _displayNode(nullptr)
    , _avatarRenderer(nullptr)
{}

Avatar::~Avatar()
{
    if (_avatarRenderer) _avatarRenderer->release();
    if (_displayNode) _displayNode->release();
}

bool Avatar::isPlaying() const
{
    return true;
}

bool Avatar::isPaused() const
{
    return true;
}

bool Avatar::isLoop() const
{
    return true;
}

bool Avatar::load(const std::string &path, const std::string &name)
{
    if (_displayNode)
    {
        if (_avatarRenderer) _avatarRenderer->removeFromParent();
    }
    else
    {
        _displayNode = cocos2d::Node::create();
        _displayNode->retain();

        _avatarRenderer = cocos2d::Sprite::create();
        _avatarRenderer->retain();

        _displayNode->addChild(_avatarRenderer);
    }

    loadResources(path, name, "stand");
    loadResources(path, name, "run");

    for (int i = (int)FaceDir::FRONT; i <= (int)FaceDir::LEFT_DOWN; ++i)
    {
        char szName[128] = {0};
        auto info = getFaceName((FaceDir)i);
        sprintf(szName, "%s_stand_%s", name.c_str(), info.first.c_str());
        createAnimation(szName);

        char szName1[128] = {0};
        sprintf(szName1, "%s_run_%s", name.c_str(), info.first.c_str());
        createAnimation(szName1);
    }

    return true;
}

void Avatar::play(const std::string &name, bool loop, const std::function<void()>& callback)
{
    _avatarRenderer->stopAllActions();
    auto role = getEntity()->getComponent<Role>();
    const std::string& roleAvatarName = role->getName();
    auto faceInfo = getFaceName(role->getFaceDir());
    auto str = cocos2d::StringUtils::format("%s_%s_%s", roleAvatarName.c_str(), name.c_str(), faceInfo.first.c_str());
    auto ani = GameModule::get<AnimationManager>()->getAnimation(str);
    if (ani)
    {
        auto animate = cocos2d::Animate::create(ani);
        if (loop)
        {
            auto repeat = RepeatForever::create(animate);
            _avatarRenderer->runAction(repeat);
        }
        else
        {
            auto call = CallFunc::create([=]{
                if (callback) callback();
            });
            auto seq = Sequence::create(animate, call, NULL);
            _avatarRenderer->runAction(seq);
        }
        _avatarRenderer->setFlippedX(faceInfo.second);
    }
}

void Avatar::playQueued(const std::string &name, bool loop, const std::function<void()>& callback)
{
}

void Avatar::pause()
{

}

void Avatar::resume()
{

}

void Avatar::stop()
{
}

bool Avatar::hasAnimation(const std::string &name)
{
    return GameModule::get<AnimationManager>()->hasAnimation(name);
}

void Avatar::onUpdate(float dt)
{
}

cocos2d::Node* Avatar::getDisplayNode()
{
    return _displayNode;
}

cocos2d::Sprite* Avatar::getAvatarRenderer()
{
    return _avatarRenderer;
}

END_NS_ECS
