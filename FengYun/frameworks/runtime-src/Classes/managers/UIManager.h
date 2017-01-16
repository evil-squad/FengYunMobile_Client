/**
 * @file  UIManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <functional>

#include "MathTypes.h"

#include "GUI/Layer.h"
#include "GameModule.h"

BEGIN_NS_FY

class UIManager : public GameModule
{
public:
    UIManager();
    ~UIManager();

    void initUIRect();

    const Rect& getUIRect() const { return _uiRect; }

    void registerUILayer(gui::Layer* layer);
    void unregisterUILayer(gui::Layer* layer);

    gui::Layer* getUILayer() { return _uiLayer; }

private:
    Rect _uiRect;
    gui::Layer* _uiLayer;
};

END_NS_FY

#endif /* UIMANAGER_H */
