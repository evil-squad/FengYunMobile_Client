/**
 * @file  Attack.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Attack.h"
#include "ECS/Role.h"

BEGIN_NS_FSM

Attack::Attack()
{}

Attack::~Attack()
{}

void Attack::onEnter()
{
    auto role = getBaseData()->getRole();
    auto avatar = role->getAvatar();
    avatar->play("attack", false, [=](){
        getFsm()->replaceState("Standing");
    });
}

void Attack::onExit()
{

}

void Attack::onDidUpdate()
{

}

END_NS_FSM
