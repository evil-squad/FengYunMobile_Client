/**
 * @file  Motor.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Motor.h"
#include "misc/Physics.h"
#include "Scenes/GameScene.h"

BEGIN_NS_FSM

Motor::Motor(const ecs::ComponentHandle<ecs::Role>& role)
    : _role(role)
    , _accel(Vector3::ZERO)
    , _speed(Vector3::ZERO)
    , _grounded(true)
    , _enabled(true)
    , _gravity(Physics::gravity())
{}

Motor::~Motor()
{}

void Motor::move(const Vector3 &delta)
{
    if (!_enabled) return ;

    auto trans = _role->getTransform();
    auto pos = trans->getPosition();

    pos += delta;

    if (_grounded)
    {
        pos.z = 0;
    }

    trans->setPosition(pos);
}

void Motor::move(float dt, bool hasGravity)
{
    if (!_enabled) return ;

    _speed += _accel * dt;
    if (hasGravity)
        _speed.z = _gravity * dt;

    if (_grounded && _speed.z < 0) _speed.z = 0 ;

    move(_speed * dt);
}

END_NS_FSM
