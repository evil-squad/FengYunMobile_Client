/**
 * @file  Avatar.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_AVATAR_H
#define ECS_AVATAR_H

#include "Component.h"
#include "MathTypes.h"

namespace cocos2d
{
    class Node;
    class Sprite;
    class Animation;
}

BEGIN_NS_ECS

class Avatar : public Component
{
public:
    Avatar();
    virtual ~Avatar();

    bool isPlaying() const;
    bool isLoop() const;
    bool isPaused() const;

    bool load(const std::string& path, const std::string& name);
    void play(const std::string& name, bool loop, const std::function<void()>& callback = nullptr);
    void playQueued(const std::string& name, bool loop, const std::function<void()>& callback = nullptr);

    void pause();
    void resume();

    void stop();

    bool hasAnimation(const std::string& name);

    cocos2d::Node* getDisplayNode();
    cocos2d::Sprite* getAvatarRenderer();

protected:
    void onUpdate(float dt) override;

private:
    cocos2d::Node* _displayNode;
    cocos2d::Sprite* _avatarRenderer;

};

template <>
class component_traits<Avatar>
{
public:
    typedef Component parent_type;
    static const char* name() { return "Avatar"; }
    static int flags() { return ComponentFlags::HAS_UPDATE; }
    static Component* create() { return new Avatar(); }
};

END_NS_ECS
#endif /* ECS_AVATAR_H */
