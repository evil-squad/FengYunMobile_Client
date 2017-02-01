/**
 * @file  Motor.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_MOTOR_H
#define FSM_MOTOR_H

#include "fsmbase.h"
#include "ECS/Role.h"

BEGIN_NS_FSM

class Motor
{
public:
    Motor(const ecs::ComponentHandle<ecs::Role>& role);
    ~Motor();

    bool isEnabled() const { return _enabled; }
    void setEnabled(bool value) { _enabled = value; }

    bool isGrounded() const { return _grounded; }

    const Vector3& getAccel() const { return _accel; }
    void setAccel(const Vector3& accel) { _accel = accel; }

    const Vector3& getSpeed() const { return _speed; }
    void setSpeed(const Vector3& speed) { _speed = speed; }

    float getGravity() const { return _gravity; }
    void setGravity(float g) { _gravity = g; }

    void move(const Vector3& delta);
    void move(float dt, bool hasGravity = true);

private:
    ecs::ComponentHandle<ecs::Role> _role;
    Vector3 _accel;
    Vector3 _speed;
    bool _grounded;
    bool _enabled;
    float _gravity;
};


END_NS_FSM
#endif /* FSM_MOTOR_H */
