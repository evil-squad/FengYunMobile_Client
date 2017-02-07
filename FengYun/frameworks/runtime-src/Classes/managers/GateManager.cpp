/**
 * @file  GateManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GateManager.h"
#include "GameConfigLoader.h"

BEGIN_NS_FY

struct GateManager::PrivateData
{

};

GateManager::GateManager()
{
    _data = new PrivateData();
}

GateManager::~GateManager()
{
    delete _data;
}

void GateManager::onInitialize()
{

}

void GateManager::onRelease()
{

}

void GateManager::onLoadConfig(fy::GameConfigLoader *loader)
{
    
}


END_NS_FY
