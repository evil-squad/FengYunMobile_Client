/**
 * @file  input.inc.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef input_inc_h
#define input_inc_h

#include "GameInput.h"
#include "LuaHelpUtils.h"

DEF_LUA_FUNC(addGameInputEvent)
{
    bool ok = true;
    int t;
    ok &= luaval_to_int32(L, 1, &t);
    if (ok)
    {
        fy::InputEventType type = (fy::InputEventType)t;
        if (type == fy::InputEventType::AXIS_EVENT)
        {
            int id;
            double x;
            double y;
            int a;
            ok &= luaval_to_int32(L, 2, &id);
            ok &= luaval_to_number(L, 3, &x);
            ok &= luaval_to_number(L, 4, &y);
            ok &= luaval_to_int32(L, 5, &a);
            if (ok)
            {
                fy::GameInput::getInstance()->addInputEvent(id, cocos2d::Vec2(x, y), (fy::JoystickDir)a);
                return 0;
            }
        }
        else if (type == fy::InputEventType::BUTTON_EVENT)
        {
            int id;
            bool v;
            ok &= luaval_to_int32(L,2, &id);
            ok &= luaval_to_boolean(L, 3, &v);
            if (ok)
            {
                fy::GameInput::getInstance()->addInputEvent(id, v);
                return 0;
            }
        }
    }
    RET_ARG_ERROR(addGameInputEvent);
}

DEF_LUA_FUNC(getInputAxisId)
{
    bool ok = true;
    std::string name;

    ok &= luaval_to_std_string(L, 1, &name);

    if (ok)
    {
        auto v = fy::GameInput::getInstance()->getAxisId(name);
        lua_pushnumber(L, v);
        return 1;
    }
    RET_ARG_ERROR(getInputAxisId);
}

DEF_LUA_FUNC(getInputButtonId)
{
    bool ok = true;
    std::string name;

    ok &= luaval_to_std_string(L,1, &name);

    if (ok)
    {
        auto v = fy::GameInput::getInstance()->getButtonId(name);
        lua_pushnumber(L, v);
        return 1;
    }
    RET_ARG_ERROR(getInputButtonId);
}

static int lua_getinput_GameInput_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S, 1, "GameInput", 0, &tolua_err)) goto tolua_lerror;
#endif
    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if (!ok)
        {
            return 0;
        }

        fy::GameInput* ret = fy::GameInput::getInstance();
        tolua_pushusertype(tolua_S, (void*)ret, "GameInput");
        return 1;
    }

    DBG_LOG("%s has wrong number of arguments :%d, was expecting %d\n", "getInstance", argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
        tolua_lerror:
        tolua_error(tolua_S, "#ferror in function 'lua_gameinput_GameInput_getInstance'.", &tolua_err);
#endif
    return 0;
}

static void extendGameInput(lua_State* L)
{
    lua_pushstring(L, "GameInput");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L, -1))
    {
        tolua_function(L, "getInstance", lua_getinput_GameInput_getInstance);
    }
    lua_pop(L, 1);
}

inline static void registerInputFunctions(lua_State* L)
{
    TOLUA_FUNC(addGameInputEvent);
    TOLUA_FUNC(getInputAxisId);
    TOLUA_FUNC(getInputButtonId);

    extendGameInput(L);
}

#endif /* input_inc_h */
