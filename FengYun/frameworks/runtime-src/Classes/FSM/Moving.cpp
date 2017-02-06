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
{
}

Moving::~Moving()
{
}

void Moving::onEnter()
{
    auto data = getBaseData();
    auto avatar = getBaseData()->getRole()->getAvatar();
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

    auto data = getBaseData();

    if (_axis.x < 0)
        data->getRole()->setFaceDir(fy::FaceDir::LEFT);
    else if (_axis.x > 0)
        data->getRole()->setFaceDir(fy::FaceDir::RIGHT);

    if (_axis.isZero())
        getFsm()->replaceState("Standing");
}

END_NS_FSM
