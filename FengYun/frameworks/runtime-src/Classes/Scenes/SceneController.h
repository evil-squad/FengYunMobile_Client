/**
 * @file  SceneController.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENES_SCENECONTROLLER_H
#define SCENES_SCENECONTROLLER_H

#include "scenebase.h"
#include <functional>
#include "MathTypes.h"
#include "RoleTypes.h"

BEGIN_NS_SCENES

class SceneController
{
public:
    SceneController() {}
    virtual ~SceneController() {}

    virtual void onSceneEnter() = 0;
    virtual void onSceneExit() = 0;
    virtual void onSceneUpdate(float dt) = 0;
};

END_NS_SCENES
#endif /* SCENES_SCENECONTROLLER_H */
