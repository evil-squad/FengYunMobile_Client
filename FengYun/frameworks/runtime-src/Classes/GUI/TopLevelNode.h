/**
 * @file  TopLevelNode.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GUI_TOPLEVELNODE_H
#define GUI_TOPLEVELNODE_H

#include "cocos2d.h"

namespace gui
{
    class TopLevelNode : public cocos2d::Node
    {
    public:
        virtual void setCloseCallback(std::function<void()> cb)
        {
            _closeCallback = cb;
        }

        virtual void refresh(const std::function<void()>& cb)
        {
            if (cb) cb();
        }

        virtual void close(bool removeSelf = true)
        {
            if (_closed) return;
            _closed = true;
            if (_closeCallback) _closeCallback();
            removeAllChildren();
            if (removeSelf) removeFromParent();
        }

    private:
        bool _closed;
        std::function<void()> _closeCallback;

    CC_CONSTRUCTOR_ACCESS:
        TopLevelNode() : _closed(false), _closeCallback(nullptr) {}
        virtual ~TopLevelNode() {}

    private:
        CC_DISALLOW_COPY_AND_ASSIGN(TopLevelNode);
    };
}


#endif /* GUI_TOPLEVELNODE_H */
