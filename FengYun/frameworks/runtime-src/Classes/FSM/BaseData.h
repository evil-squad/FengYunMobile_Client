/**
 * @file  BaseData.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_BASEDATA_H
#define FSM_BASEDATA_H

#include "SharedData.h"
#include "InputProcessor.h"
#include "Motor.h"

BEGIN_NS_FSM

enum class JoystickDir
{
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class BaseData : public SharedData
{
public:
    BaseData();
    virtual ~BaseData();

    const ecs::ComponentHandle<ecs::Role>& getRole() const { return _role; }
    void setRole(const ecs::ComponentHandle<ecs::Role>& role) { _role = role; }

    bool isShakeValid() const { return _shakeValid; }
    void setShakeValid(bool value) { _shakeValid = value; }

    Motor* getMotor() { return _motor; }
    void setMotor(Motor* motor) { _motor = motor; }

    InputProcessor* getInput() { return _input; }
    void setInput(InputProcessor* input) { _input = input; }

    int getImmuneFlags() const { return _immuneFlags; }
    void setImmuneFlags(int value) { _immuneFlags = value; }

    const ecs::ComponentHandle<ecs::Role>& getInterrupter() const { return _interrupter; }
    void setInterupter(const ecs::ComponentHandle<ecs::Role>& interrupter) { _interrupter = interrupter; }

private:
    ecs::ComponentHandle<ecs::Role> _role;
    bool _shakeValid;
    int _immuneFlags;
    Motor* _motor;
    InputProcessor* _input;
    ecs::ComponentHandle<ecs::Role> _interrupter;
};

END_NS_FSM
#endif /* FSM_BASEDATA_H */
