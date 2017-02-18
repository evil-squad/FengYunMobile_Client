/**
 * @file  scene.inc.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/18.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef scene_inc_h
#define scene_inc_h

#include "gamebase.h"
#include "SceneManager.h"
#include "LuaHelpUtils.h"

USING_NS_FY;

DEF_LUA_FUNC(gotoScene)
{
    int id;
    bool ok = true;
    ok &= luaval_to_int32(L, 1, &id);
    LUA_FUNCTION func = toluafix_ref_function(L, 2, 0);
    if (ok && func)
    {
        LuaHandler h = createLuaHandler(func);
        GameModule::get<SceneManager>()->gotoScene(id, [=](){
            GetLuaStack()->executeFunctionByHandler(h->getHandler(), 0);
        });

        return 0;
    }

    RET_ARG_ERROR(gotoScene);
}

inline static void registerSceneFunctions(lua_State* L)
{
    TOLUA_FUNC(gotoScene);
}

#endif /* scene_inc_h */
