/**
 * @file  BaseState.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "BaseState.h"

BEGIN_NS_FSM

void BaseState::onInterrupted(fy::fsm::BaseState *st)
{
    getFsm()->replaceState(st->getName());
}

void BaseState::onUpdate()
{
    auto data = getBaseData();
    if (_mover)
        _mover->update(this);
    else
        data->getMotor()->move(getFsm()->getDeltaTime());

    data->getInput()->update(this);

    if (getFsm()->getNext() == nullptr)
        onDidUpdate();
}

END_NS_FSM
