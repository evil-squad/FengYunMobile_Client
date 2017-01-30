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
#include "ECS/NetRole.h"
#include "MathTypes.h"

BEGIN_NS_SCENES

class SceneController;

class GameScene final : public cocos2d::Scene
{
public:
    static GameScene* create(int id);

    int getId() const { return _id; }

CC_CONSTRUCTOR_ACCESS:
    GameScene();
    virtual ~GameScene();

    bool initWithId(int id);

    void initMap();
    void initMapTouch();

    virtual void onEnter() override;
    virtual void onExit() override;

    SceneController* getController() const { return _controller; }
    void setController(SceneController* controller);

protected:
    virtual void update(float dt) override;

    Vector2 getViewPoins() const { return _viewPoint; }
    void setViewPoint(const Vector2& pos);

protected:
    int _id;

    SceneController* _controller;

private:
    gui::Layer* _uiLayer;
    cocos2d::Node* _sceneNode;
    ecs::NetRole* _player;

    Vector2 _viewPoint;

    float _time;

private:

    void adjustVirePoint(float dt);
    void updateView();

};

END_NS_SCENES

#endif /* SCENES_GAMESCNES_H */
