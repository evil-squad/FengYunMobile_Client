/**
 * @file  UserFreeMover.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UserFreeMover.h"
#include "BaseState.h"
#include "NavSystem.h"
#include "MapManager.h"
#include "Moving.h"

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
    auto pos = st->getBaseData()->getRole()->getTransform()->getPosition();
    auto mapPos = MapManager::toMapPoint(pos);

    _adjustAxis = _axis;
    auto v = _adjustAxis.getNormalized() * (_speed * dt);
    pos = MapManager::toMapPoint(pos + Vector3(v.x, v.y, 0));

    auto& nav = *NavSystem::getInstance();
    if (!nav.isWalkable(pos))
    {
        if (v.x < 0 && !nav.isWalkable(mapPos + Vector3(-1, 0, 0)))
            _adjustAxis.x = 0;
        if (v.x > 0 && !nav.isWalkable(mapPos + Vector3(1, 0, 0)))
            _adjustAxis.x = 0;
        if (v.y < 0 && !nav.isWalkable(mapPos + Vector3(0, 1, 0)))
            _adjustAxis.y = 0;
        if (v.y > 0 && !nav.isWalkable(mapPos + Vector3(0, -1, 0)))
            _adjustAxis.y = 0;
    }
}

void UserFreeMover::updatePredicts(fy::fsm::BaseState *st, bool force)
{
    if (_serverMoving && _adjustAxis.isZero())
    {
        _serverMoving = false;
        auto role = st->getBaseData()->getRole();
        auto c = role->getScene()->getBattleController();
        if (c)
            c->onStopMove(role);
        return ;
    }

    auto v = _adjustAxis.getNormalized();
    auto vv = Vector3(v.x, v.y, 0);

    Vector3 lastWalkablePoint;
    auto pos = st->getBaseData()->getRole()->getTransform()->getPosition();
    auto curMapPos = MapManager::toMapPoint(pos);
    lastWalkablePoint = curMapPos;
    int mapGridSize = MapManager::gridSize();
    for (int i = 0; i < 8; ++ i)
    {
        pos += vv * mapGridSize;
        Vector3 mapPos = MapManager::toMapPoint(pos);

        if (NavSystem::getInstance()->isGround(mapPos) &&
            !NavSystem::getInstance()->isWalkable(mapPos))
            break;

        lastWalkablePoint = mapPos;
    }

    if (force || _predictPoint != lastWalkablePoint)
    {
        _predictPoint = lastWalkablePoint;
        Vector3 step = lastWalkablePoint - curMapPos;
        if (!step.isZero())
        {
            _serverMoving = true;
            auto role = st->getBaseData()->getRole();
            auto c = role->getScene()->getBattleController();
            if (c)
                c->onMove(role, _running, step);
        }
    }
}

void UserFreeMover::updateSpeed(fy::fsm::BaseState *st)
{
    int gridSize = MapManager::gridSize();
    _speed = ( _running ? 80 : 60) * gridSize / 10;
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
        auto c = role->getScene()->getBattleController();
        if (c)
            c->onStopMove(role);
    }

    _axis = Vector2::ZERO;
    _adjustAxis = Vector2::ZERO;
    _lastAdjustAxis = Vector2::ZERO;
    _predictPoint = Vector3::ZERO;
}

void UserFreeMover::update(fy::fsm::BaseState *st)
{
    updateSpeed(st);
    adjustAxis(st, st->getFsm()->getDeltaTime());

    if (_isNormalMoving)
    {
        _time += st->getFsm()->getDeltaTime();
        if (!_running && _time > AccelTime)
        {
            static_cast<Moving*>(st)->startRun();
            _running = true;

            updatePredicts(st, true);
        }
    }

    if (_lastAdjustAxis != _adjustAxis)
    {
        _lastAdjustAxis = _adjustAxis;
        updatePredicts(st);
    }

    if (_serverMoving)
    {
        auto& pos = st->getBaseData()->getRole()->getTransform()->getPosition();
        auto mapPos = MapManager::toMapPoint(pos);

        if (mapPos == _predictPoint)
        {
            updatePredicts(st);
        }

        auto v = _adjustAxis.getNormalized() * _speed;
        auto motor = st->getBaseData()->getMotor();
        motor->setSpeed(Vector3(v.x, v.y, 0));
        motor->move(st->getFsm()->getDeltaTime());
    }
}


END_NS_FSM
