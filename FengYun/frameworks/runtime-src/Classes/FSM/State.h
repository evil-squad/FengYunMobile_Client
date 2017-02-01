/**
 * @file  State.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_STATE_H
#define FSM_STATE_H

#include "fsmbase.h"
#include <cstddef>
#include <string>

#include "SharedData.h"
#include "DebugHelper.h"

BEGIN_NS_FSM

class Fsm;

class State
{
public:
    State() : _fsm(nullptr), _name("") {}
    virtual ~State() {}

    void initFsm(Fsm* fsm)
    {
        _fsm = fsm;
    }

    void initName(const std::string& name)
    {
        _name = name;
    }

    Fsm* getFsm() const { return _fsm; }
    const std::string& getName() const { return _name; }

    void enter() { onEnter(); }
    void exit() { onExit(); }
    void update() { onUpdate(); }

protected:
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void onUpdate() {}

private:
    Fsm* _fsm;
    std::string _name;
};

END_NS_FSM
#endif /* FSM_STATE_H */
