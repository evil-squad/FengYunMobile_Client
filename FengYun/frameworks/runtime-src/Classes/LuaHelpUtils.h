/**
 * @file  LuaHelpUtils.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef LUAHELPUTILS_H
#define LUAHELPUTILS_H

#include "CCLuaEngine.h"
#include "CCLuaValue.h"
#include "LuaBasicConversions.h"
#include "tolua_fix.h"

#include "LuaHandler.hpp"
#include "DebugHelper.h"

#define lua_pushcppstring(L, s) lua_pushstring(L, (s).c_str())
#define lua_pushcppboolean(L, b) lua_pushboolean(L, (b) ? 1 : 0)

#define GetLuaStack() cocos2d::LuaEngine::getInstance()->getLuaStack()
#define GetLuaState() cocos2d::LuaEngine::getInstance()->getLuaStack()->getLuaState()

#define DEF_LUA_FUNC(func) static int func(lua_State* L)
#define TOLUA_FUNC(func) tolua_function(L, #func, func)

#define RET_ARG_ERROR(func)                         \
    tolua_error(L, "argument error in '" #func "' function", nullptr); \
    return 0

#define LUA_PUSH_STRUCT_INT_MEM(L, val, mem)    \
    lua_pushliteral(L, #mem);                   \
    lua_pushinteger(L, (val).mem);              \
    lua_rawset(L, -3)

#define LUA_PUSH_STRUCT_NUM_MEM(L, val, mem)    \
    lua_pushliteral(L, #mem);                   \
    lua_pushnumber(L, (val).mem);               \
    lua_rawset(L, -3)

#define LUA_PUSH_STRUCT_BOOL_MEM(L, val, mem)   \
    lua_pushliteral(L, #mem);                   \
    lua_pushcppboolean(L, (val).mem);           \
    lua_rawset(L, -3)

#define LUA_PUSH_STRUCT_ENUM_MEM(L, val, mem)   \
    lua_pushliteral(L, #mem);                   \
    lua_pushinteger(L, (int)((val).mem));       \
    lua_rawset(L, -3)

inline bool lua_safecall(lua_State* L, int narg, int nresult)
{
    int functionIndex = -(narg + 1);
    lua_getglobal(L, "__G__TRACKBACK__");
    DBG_ASSERT(lua_isfunction(L, -1), "lua __G__TRACKBACK__ function not found!");
    lua_insert(L, functionIndex - 1);
    int traceback = functionIndex - 1;
    int error = lua_pcall(L, narg, nresult, traceback);
    if (error)
    {
        lua_pop(L, 2);
        return false;
    }
    lua_remove(L, -(nresult+1));
    return true;
}

#endif /* LUAHELPUTILS_H */
