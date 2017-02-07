/**
 * @file  WorldManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <vector>
#include <array>
#include <string>
#include "gamebase.h"
#include "GameModule.h"

BEGIN_NS_FY

class WorldManager : public GameModule
{
public:
    WorldManager();
    ~WorldManager();

    void onLoadConfig(GameConfigLoader* loader) override;
    void onInitialize() override;
    void onRelease() override;

    const std::vector<int>& searchPath(int aMap, int bMap);

private:
    struct PrivateData;

    PrivateData* _data;
};


END_NS_FY
#endif /* WORLDMANAGER_H */
