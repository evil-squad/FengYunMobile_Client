/**
 * @file  PlayerNavigating.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_PLAYERNAVIGATING_H
#define ECS_PLAYERNAVIGATING_H

#include "BaseState.h"
#include "ECS/NavAgent.h"

BEGIN_NS_FSM

class UserInputProcessor;
class PlayerNavigating : public BaseState
{
    PlayerNavigating(const ecs::ComponentHandle<ecs::NavAgent>& agent);
    virtual ~PlayerNavigating();

protected:
    void onEnter() override;
    void onExit() override;
    void onDidUpdate() override;

    void onInterrupted(BaseState* st) override;

private:
    ecs::ComponentHandle<ecs::NavAgent> _agent;

    void startNavigating();
    void stopNavigating();
    void checkTargetDone();
};

END_NS_FSM
#endif /* ECS_PLAYERNAVIGATING_H */
