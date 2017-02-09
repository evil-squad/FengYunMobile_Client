/**
 * @file  RoleManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/8.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include "gamebase.h"
#include "RoleData.h"
#include "GameModule.h"

BEGIN_NS_FY

class RoleManagerData_t;

class RoleManager : public GameModule
{
public:
    RoleManager();
    ~RoleManager();
    
    const RoleData* getPlayerData();
    RoleData* getEditablePlayerData();

private:
    RoleManagerData_t* _data;
};


END_NS_FY
#endif /* ROLEMANAGER_H */
