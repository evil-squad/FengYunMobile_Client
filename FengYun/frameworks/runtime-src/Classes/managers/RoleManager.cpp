/**
 * @file  RoleManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/8.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "RoleManager.h"

BEGIN_NS_FY

struct RoleManagerData_t
{
    RoleData* playerData;

    RoleManagerData_t()
    {
        playerData = new RoleData();
    }

    ~RoleManagerData_t()
    {
        if (playerData)
        {
            delete playerData;
            playerData = nullptr;
        }
    }
};

RoleManager::RoleManager()
{
    _data = new RoleManagerData_t();
}

RoleManager::~RoleManager()
{
    delete _data;
}

const RoleData* RoleManager::getPlayerData()
{
    return _data->playerData;
}

RoleData* RoleManager::getEditablePlayerData()
{
    return _data->playerData;
}


END_NS_FY
