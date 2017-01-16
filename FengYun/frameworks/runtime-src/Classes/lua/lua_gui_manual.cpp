/**
 * @file  lua_gui_manual.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
 */

#include "lua_gui_manual.hpp"

#include "GUI.h"
#include "LuaHandler.hpp"
#include "DebugHelper.h"

#include "cocos2d.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

static int lua_gui_TopLevelNode_setCloseCallback(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;
    gui::TopLevelNode* self = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"gui.TopLevelNode",0,&tolua_err)) goto tolua_lerror;
#endif

    self = static_cast<gui::TopLevelNode*>(tolua_tousertype(L,1,0));

#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(L,"invalid 'self' in function 'lua_gui_TopLevelNode_setCloseCallback'\n", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaHandler h = createLuaHandler(toluafix_ref_function(L,2,0));
        self->setCloseCallback([=] {
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(h->getHandler(), 0);
        });
        return 0;
    }

    DBG_LOG("'setCloseCallback' function of Control has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setCloseCallback'.",&tolua_err);
    return 0;
#endif
}

static int lua_gui_Window_setUnreceiveTouchCallback(lua_State* L)
{
    if (nullptr == L)
        return 0;

    int argc = 0;
    gui::Window* self = nullptr;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"gui.Window",0,&tolua_err)) goto tolua_lerror;
#endif

    self = static_cast<gui::Window*>(tolua_tousertype(L,1,0));

#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(L,"invalid 'self' in function 'lua_gui_Window_setUnreceiveTouchCallback'\n", NULL);
        return 0;
    }
#endif
    argc = lua_gettop(L) - 1;

    if (1 == argc)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LuaHandler h = createLuaHandler(toluafix_ref_function(L,2,0));
        self->setUnreceiveTouchCallback([=](const cocos2d::Vec2& v) {
            vec2_to_luaval(L, v);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(h->getHandler(), 1);
        });
        return 0;
    }

    DBG_LOG("'setUnreceiveTouchCallback' function of Control has wrong number of arguments: %d, was expecting %d\n", argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L,"#ferror in function 'setUnreceiveTouchCallback'.",&tolua_err);
    return 0;
#endif
}

static void extendTopLevelNode(lua_State* L)
{
    lua_pushstring(L, "gui.TopLevelNode");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setCloseCallback", lua_gui_TopLevelNode_setCloseCallback);
    }
    lua_pop(L, 1);
}

static void extendWindow(lua_State* L)
{
    lua_pushstring(L, "gui.Window");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setUnreceiveTouchCallback", lua_gui_Window_setUnreceiveTouchCallback);
    }
    lua_pop(L, 1);
}

int register_all_gui_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    extendTopLevelNode(L);
    extendWindow(L);

    return 0;
}
