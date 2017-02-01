/**
 * @file  BaseMover.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_BASEMOVER_H
#define FSM_BASEMOVER_H

#include "fsmbase.h"

BEGIN_NS_FSM

class BaseState;

class BaseMover
{
public:
    virtual ~BaseMover() {}

    virtual void enter(BaseState* st) {}
    virtual void exit(BaseState* st) {}
    virtual void update(BaseState* st) = 0;
};

END_NS_FSM
#endif /* FSM_BASEMOVER_H */
