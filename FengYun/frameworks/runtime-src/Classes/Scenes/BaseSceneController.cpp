/**
 * @file  BaseSceneController.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "BaseSceneController.h"

BEGIN_NS_SCENES

BaseSceneController::BaseSceneController(GameScene* scene)
    : _scene(scene)
{}

BaseSceneController::~BaseSceneController()
{}

END_NS_SCENES
