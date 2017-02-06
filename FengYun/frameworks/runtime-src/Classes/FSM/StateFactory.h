/**
 * @file  StateFactory.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_STATEFACTORY_H
#define FSM_STATEFACTORY_H

#include "fsmbase.h"
#include <vector>

BEGIN_NS_FSM

class Fsm;

class StateFactory
{
public:
    static void addRoleBaseStates(Fsm* fsm);

private:
    StateFactory();
    ~StateFactory();
};
END_NS_FSM
#endif /* FSM_STATEFACTORY_H */
