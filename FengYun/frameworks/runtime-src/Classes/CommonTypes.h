/**
 * @file  CommonTypes.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include "gamebase.h"

BEGIN_NS_FY

enum class JoystickDir
{
    NONE = 0,
    FRONT,
    RIGHT_DOWN,
    RIGHT,
    RIGHT_UP,
    BACK,
    LEFT_UP,
    LEFT,
    LEFT_DOWN
};

END_NS_FY
#endif /* COMMONTYPES_H */
