/**
 * @file  Window.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Window.h"

USING_NS_CC;

static cocos2d::Vec2 beganPos;

namespace gui
{
    Window* Window::create(gui::Window::Type type, float width, float height)
    {
        return create(type, 0, 0, width, height);
    }

    Window* Window::create(gui::Window::Type type, float x, float y, float width, float height)
    {
        Window* w = new Window();
        if (w && w->init(type, x, y, width, height))
        {
            w->autorelease();
            return w;
        }

        CC_SAFE_DELETE(w);
        return nullptr;
    }

    Window::Window()
    : _type(Type::FIXED)
    , _autoFit(false)
    {
    }

    Window::~Window()
    {
    }

    bool Window::init(gui::Window::Type type, float x, float y, float width, float height)
    {
        _type = type;
        setPosition(Vec2(x, y));
        setContentSize(Size(width, height));

        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);

        touchListener->onTouchBegan = CC_CALLBACK_2(Window::onTouchBegan, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Window::onTouchEnded, this);

        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

        setAutoFit(true);

        return true;
    }

    void Window::setAutoFit(bool autoFit)
    {
        if (_autoFit != autoFit)
        {
            _autoFit = autoFit;
            if (autoFit)
            {
                auto winSize = Director::getInstance()->getVisibleSize();
                auto nodeSize = this->getContentSize();
                float xs = winSize.width / nodeSize.width;
                float ys = winSize.height / nodeSize.height;
                this->setScale(std::min(1.0f, std::min(xs, ys)));
            }
            else
            {
                this->setScale(1.0f);
            }
        }
    }

    void Window::setUnreceiveTouchCallback(const std::function<void (const cocos2d::Vec2 &)> &callback)
    {
        _unreceiveTouchCallback = callback;
    }

    bool Window::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
    {
        beganPos = touch->getLocation();
        return true;
    }

    void Window::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
    {
        auto p = touch->getLocation();
        auto dis = p.getDistance(beganPos);
        if (dis < 30)
        {
            if (_unreceiveTouchCallback) _unreceiveTouchCallback(touch->getLocation());
        }
    }
}
