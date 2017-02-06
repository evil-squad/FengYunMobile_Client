/**
 * @file  Standing.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Standing.h"

BEGIN_NS_FSM

void Standing::onEnter()
{
    auto data = getBaseData();
    data->getRole()->getAvatar()->play("stand", true);
    data->getMotor()->setSpeed(Vector3::ZERO);
    data->getMotor()->setAccel(Vector3::ZERO);
    data->getInput()->onStanding();
}

void Standing::onExit()
{

}

void Standing::onDidUpdate()
{
    
}

END_NS_FSM
