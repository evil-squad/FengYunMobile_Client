/**
 * @file  SceneManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENEMANGER_H
#define SCENEMANGER_H

#include "gamebase.h"
#include "GameModule.h"
#include "Scenes/GameScene.h"

BEGIN_NS_FY

class SceneManager : public GameModule
{
public:
    SceneManager();
    ~SceneManager();

    void onInitialize() override;
    void onRelease() override;

    scenes::GameScene* getCurrent();

    void gotoUIScene(const std::string& name, const std::function<void()>& enterCb);

    void gotoScene(int id, const std::function<void()>& callback);

private:
    struct PrivateData;

    PrivateData* _data;
};

END_NS_FY

#endif /* SCENEMANGER_H */
