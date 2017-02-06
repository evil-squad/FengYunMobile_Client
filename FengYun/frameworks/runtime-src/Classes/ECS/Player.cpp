/**
 * @file  Player.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Player.h"
#include "Entity.h"
#include "World.h"

#include "FSM/Fsm.h"
#include "FSM/BaseData.h"
#include "FSM/UserInputProcessor.h"
#include "FSM/StateFactory.h"

USING_NS_FSM;

BEGIN_NS_ECS

ComponentHandle<Player> Player::_current = nullptr;

void Player::setCurrent(const ComponentHandle<fy::ecs::Player> &player)
{
    _current = player;
}

const ComponentHandle<Player>& Player::getCurrent()
{
    return _current;
}

ComponentHandle<Player> Player::create(fy::RoleJob job)
{
    auto e = World::getInstance()->createEntity();
    auto c = e->addComponent<Player>();
    c->init(job);
    return c;
}

Player::Player()
: Role(component_type<Player>(), RoleType::PLAYER)
{
}

Player::~Player()
{
}

void Player::init(fy::RoleJob job)
{
    getEntity()->setName("Hero");

    Role::init("man", true);

    auto input = new UserInputProcessor(_fsm, _fsmData);
    _fsmData->setInput(input);

    StateFactory::addRoleBaseStates(_fsm);
}

void Player::onAwake()
{
}

void Player::onStart()
{
    Role::onStart();

    _fsm->runState("Standing", _fsmData);
}

void Player::onDestroy()
{
    Role::onDestroy();
}

bool Player::navToNpc(int npcId)
{
    return true;
}

bool Player::navToGate(int gateId)
{
    return true;
}

bool Player::navToCollectItem(int collectId)
{
    return true;
}

bool Player::navToTreasure(int itemId)
{
    return true;
}

bool Player::navToPos(const Vector3 &pos)
{
    return true;
}

void Player::stopNavigation()
{
    
}

END_NS_ECS
