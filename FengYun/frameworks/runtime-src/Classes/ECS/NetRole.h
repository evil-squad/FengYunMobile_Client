/**
 * @file  NetRole.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_NET_ROLE_H
#define ECS_NET_ROLE_H

#include "cocos2d.h"
#include "ecsbase.h"
#include "RoleTypes.h"

BEGIN_NS_ECS

class NetRole : public cocos2d::Node
{
public:
    NetRole();
    ~NetRole();

    static NetRole* create();

    FaceDir getFaceDir() const { return _faceDir; }
    void setFaceDir(FaceDir value);

    void onStart();

    void onMove(const cocos2d::Vec2& endPos, const std::function<void()>& cb);

    void checkAngle(float angle);

private:
    cocos2d::Map<std::string, cocos2d::Animation*> _animations;

    bool init() override;

    void playAnimation(const std::string& state);

private:
    FaceDir _faceDir;

    cocos2d::Sprite* _skin;
    cocos2d::Label* _nameLabel;

};

END_NS_ECS

#endif /* ECS_NET_ROLE_H */
