/**
 * @file  Panel.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Panel.h"

USING_NS_CC;

namespace gui
{
    float Panel::_initialScale = 1.0f;

    Panel* Panel::create(float width, float height)
    {
        return create(0, 0, width, height, _initialScale);
    }

    Panel* Panel::create(float width, float height, float scale)
    {
        return create(0, 0, width, height, scale);
    }

    Panel* Panel::create(float x, float y, float width, float height)
    {
        return create(x, y, width, height, _initialScale);
    }

    Panel* Panel::create(float x, float y, float width, float height, float scale)
    {
        Panel* p = new Panel();
        if (p && p->init(x, y, width, height, scale))
        {
            p->autorelease();
            return p;
        }

        CC_SAFE_DELETE(p);
        return nullptr;
    }

    Panel::Panel()
    {
    }

    Panel::~Panel()
    {
    }

    bool Panel::init(float x, float y, float width, float height, float scale)
    {
        this->setPosition(Vec2(x, y));
        this->setContentSize(Size(width, height));
        this->setScale(scale);
        return true;
    }
}
