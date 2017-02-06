/**
 * @file  Attack.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_ATTACK_H
#define FSM_ATTACK_H

#include "BaseState.h"

BEGIN_NS_FSM

class Attack : public BaseState
{
public:
    Attack();
    virtual ~Attack();

protected:
    void onEnter() override;
    void onExit() override;
    void onDidUpdate() override;
};

END_NS_FSM
#endif /* FSM_ATTACK_H */
