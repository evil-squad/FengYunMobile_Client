/**
 * @file  GameScene.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENES_GAMESCNES_H
#define SCENES_GAMESCNES_H

#include "scenebase.h"
#include "cocos2d.h"
#include "GUI/Layer.h"

BEGIN_NS_SCENES

class GameScene final : public cocos2d::Scene
{
public:
    static GameScene* create(int id);

    int getId() const { return _id; }

CC_CONSTRUCTOR_ACCESS:
    GameScene();
    virtual ~GameScene();

    bool initWithId(int id);

    virtual void onEnter() override;
    virtual void onExit() override;

protected:
    virtual void update(float dt) override;

protected:
    int _id;

private:
    gui::Layer* _uiLayer;

    cocos2d::Node* _sceneNode;

};

END_NS_SCENES

#endif /* SCENES_GAMESCNES_H */
