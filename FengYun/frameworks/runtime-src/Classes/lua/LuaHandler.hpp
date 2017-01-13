/**
 * @file  LuaHandler.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef LUAHANDLER_H
#define LUAHANDLER_H

#include <memory>
#include "CCLuaEngine.h"

class LuaHandlerProxy
{
public:
    inline LuaHandlerProxy(int handler)
    {
        _handler = handler;
    }

    inline ~LuaHandlerProxy()
    {
        if (_handler != 0)
        {
            cocos2d::LuaEngine::getInstance()->removeScriptHandler(_handler);
            _handler = 0;
        }
    }

    inline int getHandler() const { return _handler; }

private:
    int _handler;
};

typedef std::shared_ptr<LuaHandlerProxy> LuaHandler;
static inline LuaHandler createLuaHandler(int handler)
{
    return LuaHandler(new LuaHandlerProxy(handler));
}

#endif /* LUAHANDLER_H */
