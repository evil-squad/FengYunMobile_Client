/**
 * @file  GateManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GATEMANAGER_H
#define GATEMANAGER_H

#include "gamebase.h"
#include "GameModule.h"

BEGIN_NS_FY

class GateManager : public GameModule
{
public:
    GateManager();
    ~GateManager();

    void onInitialize() override;
    void onRelease() override;

    void onLoadConfig(GameConfigLoader* loader) override;

private:
   struct PrivateData;

    PrivateData* _data;
};

END_NS_FY
#endif /* GATEMANAGER_H */
