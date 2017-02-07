/**
 * @file  AnimationManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "AnimationManager.h"
#include "cocos2d.h"
#include "DebugHelper.h"

USING_NS_CC;

BEGIN_NS_FY

struct AnimationManager::PrivateData
{
    Map<std::string, Animation*> animations;

    bool hasAnimation(const std::string& name)
    {
        return animations.find(name) != animations.end();
    }
};

AnimationManager::AnimationManager()
{
    _data = new PrivateData();
}

AnimationManager::~AnimationManager()
{
    delete _data;
}

void AnimationManager::onInitialize()
{
}

void AnimationManager::onRelease()
{
}

void AnimationManager::addAnimation(const std::string &name, cocos2d::Animation *ani)
{
    _data->animations.insert(name, ani);
}

void AnimationManager::removeAnimation(const std::string &name)
{
    _data->animations.erase(name);
}

cocos2d::Animation* AnimationManager::getAnimation(const std::string &name) const
{
    for (auto iter :_data->animations)
    {
        DBG_LOG("%s", iter.first.c_str());
    }
    return _data->animations.at(name);
}

bool AnimationManager::hasAnimation(const std::string &name)
{
    return _data->hasAnimation(name);
}

END_NS_FY
