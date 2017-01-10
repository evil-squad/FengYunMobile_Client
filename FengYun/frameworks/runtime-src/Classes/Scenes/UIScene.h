/**
 * @file  UIScene.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENES_UISCENE_H
#define SCENES_UISCENE_H

#include "scenebase.h"
#include "cocos2d.h"
#include "GUI.h"

BEGIN_NS_SCENES

class UIScene : public cocos2d::Scene
{
public:
    static UIScene* create(const std::string& name, const std::function<void()>& enterCb);

CC_CONSTRUCTOR_ACCESS:
    UIScene();
    virtual ~UIScene();

    bool init(const std::string& name, const std::function<void()>& enterCb);
    void onEnter();
    void onExit();

private:
    gui::Layer* _uiLayer;
    std::function<void()> _enterCb;

};

END_NS_SCENES

#endif /* SCENES_UISCENE_H */
