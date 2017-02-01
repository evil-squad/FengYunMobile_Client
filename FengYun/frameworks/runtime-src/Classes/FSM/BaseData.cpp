/**
 * @file  BaseData.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "BaseData.h"

BEGIN_NS_FSM

BaseData::BaseData()
    : _role(nullptr)
    , _shakeValid(false)
    , _immuneFlags(0)
    , _motor(nullptr)
    , _input(nullptr)
{}

BaseData::~BaseData()
{
    if (_motor)
    {
        delete _motor;
        _motor = nullptr;
    }

    if (_input)
    {
        delete _input;
        _input = nullptr;
    }
}



END_NS_FSM
