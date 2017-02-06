/**
 * @file  StateFactory.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "StateFactory.h"
#include "Standing.h"
#include "Moving.h"
#include "Attack.h"
#include "Dead.h"

BEGIN_NS_FSM

static inline BaseState* createBaseState(const std::string& name, BaseState* st)
{
    st->initName(name);
    return st;
}

void StateFactory::addRoleBaseStates(fy::fsm::Fsm *fsm)
{
    fsm->addState(createBaseState("Standing", new Standing()));
    fsm->addState(createBaseState("Moving", new Moving()));
    fsm->addState(createBaseState("Attack", new Attack()));
    fsm->addState(createBaseState("Dead", new Dead()));
}

END_NS_FSM
