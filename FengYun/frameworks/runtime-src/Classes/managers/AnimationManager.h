/**
 * @file  AnimationManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "gamebase.h"
#include "GameModule.h"
#include <string>

namespace cocos2d
{
    class Animation;
}

BEGIN_NS_FY

class AnimationManager : public GameModule
{
public:
    AnimationManager();
    ~AnimationManager();

    void onInitialize() override;
    void onRelease() override;

    void addAnimation(const std::string& name, cocos2d::Animation* ani);
    void removeAnimation(const std::string& name);

    cocos2d::Animation* getAnimation(const std::string& name) const;

    bool hasAnimation(const std::string& name);

private:
    struct PrivateData;

    PrivateData* _data;
};

END_NS_FY
#endif /* ANIMATIONMANAGER_H */
