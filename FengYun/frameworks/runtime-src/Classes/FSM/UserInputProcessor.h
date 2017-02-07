/**
 * @file  UserInputProcessor.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_USERINPUTPROCESSOR_H
#define FSM_USERINPUTPROCESSOR_H

#include "BaseInputProcessor.h"
#include "BaseState.h"
#include "UserFreeMover.h"
#include <deque>
#include "BaseData.h"
#include "CommonTypes.h"

namespace fy
{
    class GameInput;
}

BEGIN_NS_FSM

class UserInputProcessor : public BaseInputProcessor
{
public:
    UserInputProcessor(Fsm* fsm, BaseData* fsmData);
    ~UserInputProcessor();

    bool isInputEnabled(InputType type) override;
    void setInputEnabled(InputType type, bool value) override;

    void update(BaseState* st) override;

    void onHandleAgentMsg(net::AgentMsg msg) override;

    BaseMover* getFreeMover() override;

protected:
    void onCastSkill(int skillId) override;

private:
    bool _joystickEnabled;
    bool _jumpEnabled;
    bool _attackEnabled;
    bool _skillEnabled;

    Vector2 _inputAxis;
    JoystickDir _joystickDir;

    Vector2 _attackAxis;
    float _attackPressedTime;

    UserFreeMover* _mover;

    RoleJob _job;

    BaseState* _nextState;

private:
    bool processAttack(BaseState* st, GameInput* input, float time);
    bool processJump(BaseState* st, GameInput* input, float time);
    bool processSkills(BaseState* st, GameInput* input, float time);

    void doGroundAttack(BaseState* st, JoystickDir dir, bool isShort);
    void doAirAttack(BaseState* st, JoystickDir dir, bool isShort);

    bool doCastSkill(BaseState* st, int skillId);
};

END_NS_FSM
#endif /* FSM_USERINPUTPROCESSOR_H */
