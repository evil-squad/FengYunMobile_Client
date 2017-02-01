/**
 * @file  Fsm.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_FSM_H
#define FSM_FSM_H

#include <string>
#include <unordered_map>
#include "State.h"

BEGIN_NS_FSM

class Fsm final
{
public:
    Fsm();
    ~Fsm();

    SharedData* getShared() { return _shared; }

    State* getCurrent() const { return _current; }
    State* getNext() const { return _next; }

    float getDeltaTime() const { return _deltaTime; }
    float getTime() const { return _time; }

    void addState(State* st);
    void addState(const std::string& name, State* st);
    State* getState(const std::string& name);

    void runState(const std::string& name, SharedData* shared);
    void replaceState(const std::string& name);

    void end();
    void endImmediately();

    void update(float dt);

private:
    SharedData* _shared;

    State* _current;
    State* _next;

    bool _ending;
    float _deltaTime;
    float _time;

    std::unordered_map<std::string, State*> _states;
};

template <class T>
inline T* get_shared(Fsm* fsm)
{
    return static_cast<T*>(fsm->getShared());
}

template<class T>
inline T* get_state(Fsm* fsm, const std::string& name)
{
    return static_cast<T*>(fsm->getState(name));
}

END_NS_FSM
#endif /* FSM_FSM_H */
