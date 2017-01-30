/**
 * @file  CityController.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "CityController.h"
#include "GameApp.h"

BEGIN_NS_SCENES

CityController::CityController(GameScene* scene) : BaseSceneController(scene)
{
}

CityController::~CityController()
{}

void CityController::onSceneEnter()
{
    GameApp::getInstance()->sendEvent("enter_city_scene");
}

void CityController::onSceneExit()
{
    GameApp::getInstance()->sendEvent("leave_city_scene");
}

void CityController::onSceneUpdate(float dt)
{
}

END_NS_SCENES
