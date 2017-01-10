/**
 * @file  Window.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <functional>
#include "TopLevelNode.h"

namespace gui
{
    class Window : public TopLevelNode
    {
    public:

        enum class Type
        {
            FLOAT = 0,
            FIXED
        };

        static Window* create(Type type, float width, float height);

        static Window* create(Type type, float x, float y, float width, float height);

        bool isAutoFit() const { return _autoFit; }
        void setAutoFit(bool autoFit);

        void setUnreceiveTouchCallback(const std::function<void(const cocos2d::Vec2& v)>& callback);

    protected:
        Type _type;
        bool _autoFit;

        virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
        virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    CC_CONSTRUCTOR_ACCESS:
        Window();
        virtual ~Window();

        bool init(Type type, float x, float y, float width, float height);

    private:
        std::function<void(const cocos2d::Vec2& v)> _unreceiveTouchCallback;

        CC_DISALLOW_COPY_AND_ASSIGN(Window);
    };
}

#endif /* GUI_WINDOW_H */
