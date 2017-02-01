/**
 * @file  Agent.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_AGENT_H
#define ECS_AGENT_H

#include "Role.h"
#include "Net/SceneAgent.h"

BEGIN_NS_ECS

class Agent : public Component
{
public:
    Agent();
    virtual ~Agent();

    void init(int id) { _agentId = id; }
    int getAgentId() { return _agentId; }
    void setAgentId(int id) { _agentId = id; }

    void onHandleAgentMsg(net::AgentMsg msg);

    const ComponentHandle<Role>& getRole();

private:
    int _agentId;
    ComponentHandle<Role> _role;
};

template<>
struct component_traits<Agent>
{
    typedef Component parent_type;
    static const char* name() { return "Agent"; }
    static int flags() { return 0; }
    static Component* create() { return new Agent(); }
};

END_NS_ECS
#endif /* ECS_AGENT_H */
