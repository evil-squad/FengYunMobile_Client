/**
 * @file  CityController.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENES_CITYCONTROLLER_H
#define SCENES_CITYCONTROLLER_H

#include "BaseSceneController.h"

BEGIN_NS_SCENES

class CityController : public BaseSceneController
{
public:
    CityController(GameScene* scene);
    virtual ~CityController();

    void onSceneEnter() override;
    void onSceneExit() override;
    void onSceneUpdate(float dt) override;

private:
    void loadNpcs();
};

END_NS_SCENES
#endif /* SCENES_CITYCONTROLLER_H */
