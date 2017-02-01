/**
 * @file  Standing.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_STANDING_H
#define FSM_STANDING_H

#include "BaseState.h"

BEGIN_NS_FSM

class Standing : public BaseState
{
protected:
    void onEnter() override;
    void onExit() override;
    void onDidUpdate() override;
};

END_NS_FSM
#endif /* FSM_STANDING_H */
