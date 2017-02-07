/**
 * @file  Role.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Role.h"
#include "Entity.h"
#include "FSM/Fsm.h"
#include "FSM/BaseData.h"
#include "Renderer.h"

BEGIN_NS_ECS


static const float PLAYER_RUN_SPEED = 100;

/////////////////TODO: class Role
Role::Role(const ComponentType<Component>& type, RoleType roleType)
    : Component(type)
    , _roleType(roleType)
    , _faceDir(FaceDir::FRONT)
    , _fsm(nullptr)
    , _fsmData(nullptr)
    , _avatar(nullptr)
    , _name("")
{
}

Role::~Role()
{
}

bool Role::init(const std::string &name, bool hasFsm)
{
    _name = name;

    auto ren = getEntity()->getComponent<Renderer>();
    if (!ren)
        ren = getEntity()->addComponent<Renderer>();

    _avatar = getEntity()->addComponent<Avatar>();

    auto node = ren->getDisplayNode();

    _avatar->load("avatar/man", "man");

    auto a = _avatar->getDisplayNode();
    node->addChild(a, 10);
    
    if (hasFsm)
    {
        _fsm = new fsm::Fsm();
        _fsmData = new fsm::BaseData();

        _fsmData->setRole(ComponentHandle<Role>(this));
        _fsmData->setMotor(new fsm::Motor(_fsmData->getRole()));
    }
    return true;
}

void Role::setFaceDir(fy::FaceDir dir)
{
    _faceDir = dir;
}

const ComponentHandle<Transform>& Role::getTransform()
{
    return getEntity()->getTransform();
}

const std::string& Role::getCurrentStateName() const
{
    static std::string empty = "";
    auto st = _fsm->getCurrent();
    if (!st) return empty;
    return st->getName();
}

void Role::onUpdate(float dt)
{
    if (_fsm)
    {
        _fsm->update(dt);
    }
}

void Role::onReceive(const Event<void> &ev)
{
    if (ev.getId() == event_id<SceneAgentEvent>())
    {
        if (_fsm)
            _fsmData->getInput()->onHandleAgentMsg(ev.cast<SceneAgentEvent>().msg);
    }
}

void Role::onStart()
{

}

void Role::onDestroy()
{
    
}


END_NS_ECS
