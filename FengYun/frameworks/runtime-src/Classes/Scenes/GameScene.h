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
#include "MathTypes.h"
#include "BattleController.h"
#include "MapManager.h"

BEGIN_NS_SCENES

class SceneController;

class GameScene final : public cocos2d::Scene
{
public:
    typedef ecs::ComponentHandle<ecs::Role> Viewer;

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

    MapHandle getMap() { return _map; }
    void setViewer(Viewer viewer) { _viewer = viewer; }
    Viewer getViewer() { return _viewer; }

    Vector2 worldToLayerPoint(const Vector3& pos) const;
    Vector2 worldToUIPoint(const Vector3& pos) const;
    Vector3 uiToWorldPoint(const Vector2& pos) const;

    BattleController* getBattleController() { return _battleController; }
    void setBattleController(BattleController* controller) { _battleController = controller; }

    void onSceneBegin();
    void onSceneEnd();

protected:
    virtual void update(float dt) override;

    Vector2 getViewPoins() const { return _viewPoint; }
    void setViewPoint(const Vector2& pos);

protected:
    int _id;

   Viewer _viewer;

    SceneController* _controller;
    BattleController* _battleController;

    MapHandle _map;

private:
    gui::Layer* _uiLayer;
    cocos2d::Node* _sceneNode;

    Vector2 _viewPoint;

    float _time;

private:

    void adjustViewPoint(float dt);
    void updateView();

};

END_NS_SCENES

#endif /* SCENES_GAMESCNES_H */
