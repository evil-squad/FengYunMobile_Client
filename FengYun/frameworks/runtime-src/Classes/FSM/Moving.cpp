/**
 * @file  Moving.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Moving.h"

BEGIN_NS_FSM

Moving::Moving()
    : _isRunning(false)
    , _axis(Vector2::ZERO)
    , _dir(JoystickDir::NONE)
{
}

Moving::~Moving()
{
}

void Moving::setDir(fy::JoystickDir dir)
{
    if (dir == JoystickDir::NONE) return;
    if (_dir == dir) return;

    _dir = dir;
    auto role = getBaseData()->getRole();
    role->setFaceDir(fy::FaceDir(dir));
    auto avatar = role->getAvatar();
    avatar->play("run", true);
}

void Moving::onEnter()
{
    auto data = getBaseData();
    auto role = data->getRole();
    _dir = (JoystickDir)role->getFaceDir();
    auto avatar = role->getAvatar();
    avatar->play("run", true);
    _mover = data->getInput()->getFreeMover();
    _mover->enter(this);
}

void Moving::onExit()
{
    _mover->exit(this);
    _isRunning = false;
}

void Moving::startRun()
{
}

void Moving::onDidUpdate()
{
    if (getFsm()->getNext() != nullptr) return;

    if (_axis.isZero())
        getFsm()->replaceState("Standing");
}

END_NS_FSM
