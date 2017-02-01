/**
 * @file  Agent.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Agent.h"
#include "Entity.h"

BEGIN_NS_ECS

Agent::Agent()
    : Component(component_type<Agent>())
    , _agentId(0)
    , _role(nullptr)
{}

Agent::~Agent()
{}

void Agent::onHandleAgentMsg(net::AgentMsg msg)
{
    getRole()->emitEvent(SceneAgentEvent(msg));
}

const ComponentHandle<Role>& Agent::getRole()
{
    if (!_role)
        _role = getEntity()->getComponent<Role>();
    return _role;
}



END_NS_ECS
