/**
 * @file  BaseInputProcessor.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_BASEINPUTPROCESSOR_H
#define FSM_BASEINPUTPROCESSOR_H

#include "fsmbase.h"
#include "BaseState.h"
#include "InputProcessor.h"

BEGIN_NS_FSM

class BaseInputProcessor : public InputProcessor
{
public:
    BaseInputProcessor(Fsm* fsm, BaseData* fsmData);
    virtual ~BaseInputProcessor();

    void onStanding() override;

    void onMove(bool isRunnint, const Vector3& step) override;
    void onStopMove() override;

    void onJump(const Vector2& speed) override;

    void onCastSkill(int skillId) override;
    void onCastSkillSegment(int skillId, int seqId, int repeatCount) override;

    void onBeginSkill() override;
    void onEndSkill() override;
    void onBreakSkill() override;

protected:
    BaseState* getCurrentState() { return static_cast<BaseState*>(_fsm->getCurrent()); }

protected:
    Fsm* _fsm;
    BaseData* _fsmData;
};

END_NS_FSM
#endif /* FSM_BASEINPUTPROCESSOR_H */
