/**
 * @file  InputProcessor.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_INPUTPROCESSOR_H
#define FSM_INPUTPROCESSOR_H

#include "fsmbase.h"
#include "MathTypes.h"
#include "Net/SceneAgent.h"

BEGIN_NS_FSM

class BaseState;
class BaseMover;

enum class InputType
{
    ALL,
    JOYSTICK,
    JUMP,
    ATTACK,
    SPECIAL_SKILL
};

class InputProcessor
{
public:
    virtual ~InputProcessor() {}

    virtual bool isInputEnabled(InputType type) = 0;
    virtual void setInputEnabled(InputType type, bool value) = 0;

    virtual void onStanding() = 0;

    virtual void onMove(bool isRunning, const Vector3& step) = 0;
    virtual void onStopMove() = 0;

    virtual void onJump(const Vector2& speed) = 0;

    virtual void onCastSkill(int skillId) = 0;
    virtual void onCastSkillSegment(int skillId, int segId, int repeatCount) = 0;

    virtual void onBeginSkill() = 0;
    virtual void onEndSkill() = 0;
    virtual void onBreakSkill() = 0;

    virtual void update(BaseState* St) = 0;

    virtual BaseMover* getFreeMover() = 0;

    virtual void onHandleAgentMsg(net::AgentMsg msg) = 0;
};

END_NS_FSM
#endif /* FSM_INPUTPROCESSOR_H */
