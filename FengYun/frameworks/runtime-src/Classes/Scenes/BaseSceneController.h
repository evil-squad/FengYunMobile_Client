/**
 * @file  BaseSceneController.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENES_BASESCENECONTROLLER_H
#define SCENES_BASESCENECONTROLLER_H

#include "SceneController.h"
#include "GameScene.h"

BEGIN_NS_SCENES

class BaseSceneController : public SceneController
{
public:
    BaseSceneController(GameScene* scene);
    virtual ~BaseSceneController();

    void onSetPlayerAgent(int id, const Vector3& pt, FaceDir face, const std::function<void()>& cb) override;

protected:
    GameScene* _scene;

};

END_NS_SCENES
#endif /* SCENES_BASESCENECONTROLLER_H */
