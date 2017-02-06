/**
 * @file  Fsm.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Fsm.h"
#include "DebugHelper.h"

BEGIN_NS_FSM

Fsm::Fsm()
    :_shared(nullptr)
    , _current(nullptr)
    , _next(nullptr)
    , _ending(false)
    , _time(0)
{
}

Fsm::~Fsm()
{
    endImmediately();
    for (auto& kvp : _states)
    {
        delete kvp.second;
    }
}

void Fsm::addState(State* st)
{
    st->initFsm(this);
    DBG_ASSERT(st->getName() != "", "State no name!");
    _states[st->getName()] = st;
}

void Fsm::addState(const std::string& name, State* st)
{
    st->initFsm(this);
    st->initName(name);
    _states[name] = st;
}

State* Fsm::getState(const std::string& name)
{
    auto iter = _states.find(name);
    if (iter == _states.end()) return nullptr;

    return iter->second;
}

void Fsm::runState(const std::string& name, SharedData* shared)
{
    State* st = getState(name);

    _shared = shared;
    st->enter();
    _current = st;
}

void Fsm::replaceState(const std::string& name)
{
    State* st = getState(name);
    _next = st;
}

void Fsm::end()
{
    _ending = true;
}

void Fsm::update(float dt)
{
    _deltaTime = dt;
    _time += dt;
    if (_ending)
    {
        _ending = false;
        endImmediately();
        return;
    }

    if (!_current) return;

    _current->update();

    if (_next)
    {
        _current->exit();
        _next->enter();
        _current = _next;
        _next = nullptr;
    }
}

void Fsm::endImmediately()
{
    if (_current)
    {
        _current->exit();
        _current = nullptr;
    }

    _next = nullptr;
    _shared = nullptr;
}

END_NS_FSM
