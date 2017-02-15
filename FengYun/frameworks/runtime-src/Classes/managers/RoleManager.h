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
    class Work
    {
    public:
        virtual ~Work() {}

        virtual void markDone() = 0;
    };

    class Listener
    {
    public:
        virtual ~Listener() {}

        virtual void onPlayerDataInit() = 0;
        virtual void onPlayerDataSync(Work* work) { work->markDone(); }
        virtual void onPlayerDataReset() {}
        virtual void onPlayerLevelUp() {}
    };

    RoleManager();
    ~RoleManager();
    
    const RoleData* getPlayerData();
    RoleData* getEditablePlayerData();

    void resetPlayerData();

    void registerListener(Listener* listener);
    void unregisterListener(Listener* listener);

private:
    RoleManagerData_t* _data;
};


END_NS_FY
#endif /* ROLEMANAGER_H */
