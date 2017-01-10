/**
 * @file  Panel.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "TopLevelNode.h"

namespace gui
{
    class Panel : public TopLevelNode
    {
    public:
        static Panel* create(float width, float height);

        static Panel* create(float width, float height, float scale);

        static Panel* create(float x, float y, float width, float height);

        static Panel* create(float x, float y, float width, float height, float scale);

        static void setInitialScale(float value) { _initialScale = value; }

    CC_CONSTRUCTOR_ACCESS:
        Panel();
        virtual ~Panel();

        bool init(float x, float y, float width, float height, float scale);

    private:
        CC_DISALLOW_COPY_AND_ASSIGN(Panel);

    private:
        static float _initialScale;
    };
}

#endif /* GUI_PANEL_H */
