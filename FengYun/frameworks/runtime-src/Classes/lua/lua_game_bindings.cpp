/**
 * @file  lua_game_bindings.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GameApp.h"
#include "GameModule.h"
#include "lua_game_bindings.hpp"
#include "input.inc.hpp"

#include "UIManager.h"

DEF_LUA_FUNC(setEventHandler)
{
    std::string name;
    int func;
    bool ok = true;

    ok &= luaval_to_std_string(L, 1, &name);
    func = toluafix_ref_function(L, 2, 0);

    if (ok)
    {
        if (func != 0)
        {
            LuaHandler h = createLuaHandler(func);
            fy::GameApp::getInstance()->setEventHandler(name, [=]{
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(h->getHandler(), 0);
            });
        }
        else
        {
            fy::GameApp::getInstance()->setEventHandler(name, nullptr);
        }

        return 0;
    }

    RET_ARG_ERROR(setEventHandler);
}

DEF_LUA_FUNC(sendEvent)
{
    std::string name;
    bool ok = true;

    ok &= luaval_to_std_string(L, 1, &name);

    if (ok)
    {
        fy::GameApp::getInstance()->sendEvent(name);
        return 0;
    }
    RET_ARG_ERROR(sendEvent);
}

DEF_LUA_FUNC(getUIRect)
{
    rect_to_luaval(L, fy::GameModule::get<fy::UIManager>()->getUIRect());
    return 1;
}

DEF_LUA_FUNC(getUILayer)
{
    object_to_luaval<gui::Layer>(L, "gui.Layer", fy::GameModule::get<fy::UIManager>()->getUILayer());
    return 1;
}

int register_all_game_bindings(lua_State* L)
{
    tolua_module(L, "game", 0);
    tolua_beginmodule(L, "game");

    TOLUA_FUNC(setEventHandler);
    TOLUA_FUNC(sendEvent);

    TOLUA_FUNC(getUIRect);
    TOLUA_FUNC(getUILayer);

    registerInputFunctions(L);

    tolua_endmodule(L);
    return 0;
}
