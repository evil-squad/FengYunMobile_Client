/**
 * @file  BaseState.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_BASESTATE_H
#define FSM_BASESTATE_H

#include "Fsm.h"
#include "BaseData.h"
#include "BaseMover.h"
#include "Scenes/GameScene.h"

BEGIN_NS_FSM

class BaseState : public State
{
public:
    BaseState() : _mover(nullptr) {}

    BaseData* getBaseData()
    {
        return get_shared<BaseData>(getFsm());
    }

    const ecs::ComponentHandle<ecs::Role>& getRole()
    {
        return getBaseData()->getRole();
    }

    InputProcessor* getInput()
    {
        return getBaseData()->getInput();
    }

    Motor* getMotor()
    {
        return getBaseData()->getMotor();
    }

protected:
    BaseMover* _mover;

    void onUpdate() override;
    virtual void onInterrupted(BaseState* st);
    virtual void onDidUpdate() {}
};

END_NS_FSM
#endif /* FSM_BASESTATE_H */
