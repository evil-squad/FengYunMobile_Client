/**
 * @file  PlayerNavigating.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "PlayerNavigating.h"
#include "GateManager.h"
#include "MapManager.h"
#include "GameApp.h"
#include "ECS/Entity.h"
#include "ECS/World.h"
#include "RoleManager.h"

USING_NS_CC;

BEGIN_NS_FSM

static const int NAV_SPEED = 100;

class NavigateMover : public BaseMover
{
public:
    NavigateMover()
        : _navAgent(nullptr)
    {}

    virtual ~NavigateMover()
    {}

    void setAvent(ecs::NavAgent* agent) { _navAgent = agent; }

    void enter(BaseState* st) override
    {
        int gridSize = MapManager::gridSize();
        float speed = NAV_SPEED * gridSize / 10;
        _navAgent->setSpeed(speed);

        _targetPoint = _navAgent->getNextPoint();

        auto& pos = st->getBaseData()->getRole()->getTransform()->getPosition();
        Vector3 step = MapManager::toMapPoint(_targetPoint) - MapManager::toMapPoint(pos);

        auto input = st->getInput();
        input->onMove(false, step);
        input->onMove(true, step);
    }

    void exit(BaseState* st) override
    {
        auto& pos = st->getBaseData()->getRole()->getTransform()->getPosition();
        auto input = st->getInput();
        if (input && MapManager::toMapPoint(pos) != MapManager::toMapPoint(_targetPoint))
        {
            input->onStopMove();
        }
    }

    void update(BaseState* st) override
    {
        updateServerMove(st);
    }

private:
    ecs::NavAgent* _navAgent;
    Vector3 _targetPoint;

    void updateServerMove(BaseState* st)
    {
        auto& targetPoint = _navAgent->getNextPoint();
        if (_targetPoint != targetPoint)
        {
            _targetPoint = targetPoint;
            auto& pos = st->getBaseData()->getRole()->getTransform()->getPosition();
            Vector3 step = MapManager::toMapPoint(_targetPoint) - MapManager::toMapPoint(pos);

            auto input = st->getInput();
            if (input)
                input->onMove(true, step);
        }
    }
};

PlayerNavigating::PlayerNavigating(const ecs::ComponentHandle<ecs::NavAgent>& agent)
    : _agent(agent)
{
    auto mover = new NavigateMover();
    mover->setAvent(agent.get());
    _mover = mover;
}

PlayerNavigating::~PlayerNavigating()
{
    delete _mover;
}

void PlayerNavigating::onEnter()
{
    auto data = getBaseData();
    auto avatar = data->getRole()->getAvatar();
    avatar->play("run", true);

    startNavigating();

    _mover->enter(this);
}

void PlayerNavigating::onExit()
{
    _mover->exit(this);
}

void PlayerNavigating::onDidUpdate()
{
    auto& vel = _agent->getVelocity();

    auto data = getBaseData();

    if (vel.x < 0)
        data->getRole()->setFaceDir(fy::FaceDir::LEFT);
    else if (vel.x > 0)
        data->getRole()->setFaceDir(fy::FaceDir::RIGHT);

    checkTargetDone();
}

void PlayerNavigating::onInterrupted(fy::fsm::BaseState *st)
{
    stopNavigating();

    net::AgentNavEndData d;
    d.stateName = st->getName();
    getInput()->onHandleAgentMsg(net::AgentMsg(d));
}

void PlayerNavigating::startNavigating()
{
    auto playerData = GameModule::get<RoleManager>()->getPlayerData();
    auto target = playerData->getNavData().getNextTarget();
    switch (target->type)
    {
        case RoleNavData::TargetType::GATE:
        {

        }
            break;
        case RoleNavData::TargetType::NPC:
        {

        }
            break;
        case RoleNavData::TargetType::COLLECT_ITEM:
        {

        }
            break;
        case RoleNavData::TargetType::TREASURE:
        {

        }
            break;
        case RoleNavData::TargetType::POS:
        {

        }
            break;
        default:
            break;
    }
}

void PlayerNavigating::stopNavigating()
{
    GameModule::get<RoleManager>()->getEditablePlayerData()->getNavData().clearTargets();
    _agent->stop();
}

void PlayerNavigating::checkTargetDone()
{
    auto& navData = GameModule::get<RoleManager>()->getEditablePlayerData()->getNavData();
    auto target = navData.getNextTarget();

    if (target == nullptr) return;

    auto role = getBaseData()->getRole();

    bool isNavEnd = false;
    switch (target->type)
    {
        case RoleNavData::TargetType::GATE:
        {

        }
            break;
        case RoleNavData::TargetType::NPC:
        {

        }
            break;
        case RoleNavData::TargetType::COLLECT_ITEM:
        {

        }
            break;
        case RoleNavData::TargetType::TREASURE:
        {

        }
            break;
        case RoleNavData::TargetType::POS:
        {

        }
            break;
        default:
            break;
    }

    if (isNavEnd)
    {
        net::AgentNavEndData d;
        d.stateName = "Standing";
        getInput()->onHandleAgentMsg(net::AgentMsg(d));
    }
}

END_NS_FSM
