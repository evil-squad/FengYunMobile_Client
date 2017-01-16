/**
 * @file  lua_managers_manual.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
 */

#include "lua_managers_manual.hpp"

#include "DebugHelper.h"
#include "UIManager.h"
#include "LuaHandler.hpp"

#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaEngine.h"

static int lua_managers_UIManager_getInstance(lua_State* tolua_S)
{
    fy::UIManager* ret = fy::GameModule::get<fy::UIManager>();
    tolua_pushusertype(tolua_S, (void*)ret, "UIManager");
    return 1;
}

static void extendUIManager(lua_State* L)
{
    lua_pushstring(L, "UIManager");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "getInstance", lua_managers_UIManager_getInstance);
    }
    lua_pop(L, 1);
}

int register_all_managers_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendUIManager(L);

    return 0;
}
