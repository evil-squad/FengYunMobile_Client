/**
 * @file  Physics.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Physics.h"

#include <cstddef>

namespace fy
{
    float Physics::_gravity = 9.8;

    Physics* Physics::getInstance()
    {
        static Physics instance;
        return &instance;
    }

    Physics::Physics()
    {}

    Physics::~Physics()
    {}
}
