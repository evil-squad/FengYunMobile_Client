/**
 * @file  BattleController.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENE_BATTLECONTROLLER_H
#define SCENE_BATTLECONTROLLER_H

#include "scenebase.h"
#include "SceneController.h"
#include "MathTypes.h"
#include "RoleTypes.h"
#include "ECS/Role.h"

BEGIN_NS_SCENES

template <class T>
int battle_msg_type();

class BattleMessage
{
public:
    BattleMessage(int type)
        : _type(type)
    {
    }

    virtual ~BattleMessage() {}
    int getType() const { return _type; }

    static int new_type_id()
    {
        static int id = 0;
        return ++id;
    }

    template<class T>
    const T& as() const
    {
        if (battle_msg_type<T>() == _type)
            return *static_cast<const T*>(this);
        throw std::bad_cast();
    }

private:
    int _type;
};

template <class T>
int battle_msg_type()
{
    static int id = BattleMessage::new_type_id();
    return id;
}

class BattleController
{
public:
    typedef ecs::ComponentHandle<ecs::Role> RoleHandle;

    virtual ~BattleController() {}

    virtual void setPlayer(RoleHandle role) = 0;

    virtual void onStanding(RoleHandle role) = 0;

    virtual void onMove(RoleHandle role, bool isRunning, const Vector3& step) = 0;
    virtual void onStopMove(RoleHandle role) = 0;
    virtual void onJump(RoleHandle role, const Vector2& speed) = 0;

    virtual void onCastSkill(RoleHandle role, int skillId) = 0;
    virtual void onCastSkillSegment(RoleHandle role, int skillId, int segId, int repeatCount) = 0;

    virtual void onBeginSkill(RoleHandle role) = 0;
    virtual void onEndSkill(RoleHandle role) = 0;
    virtual void onBreakSkill(RoleHandle role, RoleHandle interrupter) = 0;

    virtual void onEmit(RoleHandle role, int emitId, float delay = 0) = 0;

    virtual void update(float dt) = 0;

    virtual void onSceneQuit() = 0;
    virtual void onBattleComplete() = 0;

    virtual void onHandleMessage(const BattleMessage& msg) {}

    virtual void onSceneEnter() {}
    virtual void onSceneExit() {}
};

END_NS_SCENES
#endif /* SCENE_BATTLECONTROLLER_H */
