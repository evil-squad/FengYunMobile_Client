/**
 * @file  BaseInputProcessor.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "BaseInputProcessor.h"

BEGIN_NS_FSM

BaseInputProcessor::BaseInputProcessor(Fsm* fsm, BaseData* fsmData)
    : _fsm(fsm)
    , _fsmData(fsmData)
{
}

BaseInputProcessor::~BaseInputProcessor()
{}

void BaseInputProcessor::onStanding()
{
    auto role = _fsmData->getRole();

}

void BaseInputProcessor::onMove(bool isRunnint, const Vector3 &step)
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onStopMove()
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onJump(const Vector2 &speed)
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onCastSkill(int skillId)
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onCastSkillSegment(int skillId, int seqId, int repeatCount)
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onBeginSkill()
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onEndSkill()
{
    auto role = _fsmData->getRole();
}

void BaseInputProcessor::onBreakSkill()
{
    auto role = _fsmData->getRole();
}

END_NS_FSM
