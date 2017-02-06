/**
 * @file  SceneAgent.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_SCENEAGENT_H
#define NET_SCENEAGENT_H

#include "netbase.h"
#include <vector>
#include <string>
#include <functional>

#include "MathTypes.h"
#include "RoleTypes.h"

BEGIN_NS_NET

enum class AgentMsgType
{
    MOVE,
    MOVE_TYPE_CHANGE,
    STOP_MOVE,
    JUMP,
    RELEASE_SPELL,
    SPELL_ATTACK,
    STANDING,
    NAV_PATH
};

struct CommondAgentData
{
    int id;
    int direct;
    int posX;
    int posY;
    int posZ;
    Vector3 speed;
    Vector3 step;
};

struct PlayerAgentData : CommondAgentData
{

};

struct MonsterAgentData : CommondAgentData
{

};

struct AgentStandingData
{
    int id;
    int posX;
    int posY;
    int posZ;
    static AgentMsgType msg_type() { return AgentMsgType::STANDING; }
};

struct AgentMoveData
{
    int id;
    int posX;
    int posY;
    int posZ;
    Vector3 speed;
    Vector3 step;

    AgentMoveData()
    {}

    static AgentMsgType msg_type() { return AgentMsgType::MOVE; }
};

struct AgentStopMoveData
{
    int id;
    int posX;
    int posY;
    int posZ;

    static AgentMsgType msg_type() { return AgentMsgType::STOP_MOVE; }
};

class AgentMsg
{
public:
    AgentMsg(const AgentMsg& other)
    {
        _type = other._type;
        _data = other._data;
    }

    template<class T>
    AgentMsg(const T& data)
    : _type(T::msg_type()), _data(&data)
    {}

    AgentMsgType getType() const { return _type; }

    template<class T>
    const T& as()
    {
        if (_type != T::msg_type()) throw std::bad_cast();
        return *static_cast<const T*>(_data);
    }

private:
    AgentMsgType _type;
    const void* _data;
};


END_NS_NET
#endif /* NET_SCENEAGENT_H */
