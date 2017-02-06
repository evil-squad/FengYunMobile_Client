/**
 * @file  Dead.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Dead.h"
#include "ECS/Role.h"

BEGIN_NS_FSM

Dead::Dead()
    : _dead(false)
    , _deadCallback(nullptr)
{}

Dead::~Dead()
{}

void Dead::onEnter()
{
    auto role = getBaseData()->getRole();
    auto avatar = role->getAvatar();
    avatar->play("dead", false, [=](){
        _dead = true;

        if (_deadCallback)
        {
            _deadCallback();
            _deadCallback = nullptr;
        }
    });
}

void Dead::onExit()
{

}

void Dead::onDidUpdate()
{

}

END_NS_FSM
