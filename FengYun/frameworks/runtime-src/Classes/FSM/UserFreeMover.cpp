/**
 * @file  UserFreeMover.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UserFreeMover.h"
#include "BaseState.h"

BEGIN_NS_FSM

static float AccelTime = 0;

UserFreeMover:: UserFreeMover()
    : _isNormalMoving(false)
    , _running(false)
    , _serverMoving(false)
    , _speed(0)
    , _time(0)
    , _axis(Vector2::ZERO)
    , _adjustAxis(Vector2::ZERO)
    , _lastAdjustAxis(Vector2::ZERO)
    , _predictPoint(Vector3::ZERO)
{
}

UserFreeMover::~UserFreeMover()
{}

void UserFreeMover::adjustAxis(fy::fsm::BaseState *st, float dt)
{
}

void UserFreeMover::updatePredicts(fy::fsm::BaseState *st, bool force)
{
}

void UserFreeMover::updateSpeed(fy::fsm::BaseState *st)
{
}

void UserFreeMover::enter(BaseState* st)
{
    if (st->getName() == "Moving")
        _isNormalMoving = true;
    else
        _isNormalMoving = false;

    _running = false;
    _time = 0;

    updateSpeed(st);
    adjustAxis(st, 0);

    updatePredicts(st);
    _lastAdjustAxis = _adjustAxis;
}

void UserFreeMover::exit(fy::fsm::BaseState *st)
{
    auto pos = st->getBaseData()->getRole()->getTransform();
    Vector3 mapPos = Vector3::ZERO;
    if (_serverMoving)
    {
        _serverMoving = false;
        auto role = st->getBaseData()->getRole();
        
    }
}

void UserFreeMover::update(fy::fsm::BaseState *st)
{
    
}


END_NS_FSM
