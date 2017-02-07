/**
 * @file  NavAgent.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "NavAgent.h"
#include "Entity.h"

#include "MapManager.h"
#include "NavSystem.h"

USING_NS_CC;

BEGIN_NS_ECS

NavAgent::NavAgent()
    : Component(component_type<NavAgent>())
    , _navigating(false)
    , _isThrough(false)
    , _speed(0)
    , _lastPos(Vector3::ZERO)
    , _velocity(Vector3::ZERO)
{}

NavAgent::~NavAgent()
{}

void NavAgent::onStart()
{
    _lastPos = getEntity()->getTransform()->getPosition();
}

void NavAgent::setDestination(const Vector3 &position)
{
    auto& nav = *NavSystem::getInstance();
    auto map = GameModule::get<MapManager>()->getCurrentMap();
    NavPath* path = nav.calculatePath(map.toMapPoint(getEntity()->getTransform()->getPosition()), map.toMapPoint(position));
    if (path)
    {
        stop();

        for (auto& v: path->path)
        {
            _path.push(map.toScenePoint(v));
        }
        _path.pop();
        nav.releasePath(path);

        _navigating = true;
    }
}

void NavAgent::stop()
{
    while (!_path.empty())
    {
        _path.pop();
    }

    _navigating = false;
}

void NavAgent::onUpdate(float dt)
{
    {
        auto& nav = *NavSystem::getInstance();
        auto map = GameModule::get<MapManager>()->getCurrentMap();
        auto pos = getEntity()->getTransform()->getPosition();
        auto mapPt = map.toMapPoint(Vector3(pos.x, pos.y, 0));

        if (pos.z < 0)
        {
            pos.z = 0;
            getEntity()->getTransform()->setPosition(pos);
        }

        if (nav.isGround(mapPt) && !nav.isWalkable(mapPt) && !!_isThrough)
        {
            pos.x = _lastPos.x;
            pos.y = _lastPos.y;
            getEntity()->getTransform()->setPosition(pos);
        }
    }

    if (_navigating)
    {
        if (_path.empty())
        {
            _navigating = false;
        }
        else
        {
            auto& pos = getEntity()->getTransform()->getPosition();
            auto& target = _path.front();

            auto d = target - pos;
            float length = d.length();
            d.scale(1.0f/length);

            float l = _speed * dt;
            if (l >= length)
            {
                l = length;
                _path.pop();
            }

            d = pos + d * l;
            getEntity()->getTransform()->setPosition(d);
        }
    }

    _velocity = (getEntity()->getTransform()->getPosition() - _lastPos) / dt;
    _lastPos = getEntity()->getTransform()->getPosition();
}

void NavAgent::resetPosition()
{
    _lastPos = getEntity()->getTransform()->getPosition();
    _velocity = Vector3::ZERO;
}

const Vector3& NavAgent::getNextPoint() const
{
    if (_navigating)
    {
        return _path.front();
    }

    return Vector3::ZERO;
}

END_NS_ECS
