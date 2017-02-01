/**
 * @file  RoleTypes.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ROLETYPES_H
#define ROLETYPES_H

#include "gamebase.h"

BEGIN_NS_FY

enum class RoleJob
{
    NONE = 0,
    BUJINGYUN,
    DIERMENG,
    NIEFENG,
    CHUCHU
};

enum class RoleType
{
    PLAYER = 0,
    NPC,
    MONSTER,
    NONE
};

enum class FaceDir
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
#endif /* ROLETYPES_H */
