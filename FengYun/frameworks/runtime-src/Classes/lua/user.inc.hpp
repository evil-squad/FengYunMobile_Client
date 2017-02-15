/**
 * @file  user.inc.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/15.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UserManager.h"
#include "LuaHelpUtils.h"

DEF_LUA_FUNC(getServers)
{
    const std::vector<fy::UserManager::ServerEntry>& servers = fy::GameModule::get<fy::UserManager>()->getServers();
    lua_newtable(L);
    for (int i = 0; i < servers.size(); ++ i)
    {
        lua_newtable(L);

        LUA_PUSH_STRUCT_INT_MEM(L, servers[i], id);
        LUA_PUSH_STRUCT_STR_MEM(L, servers[i], name);
        LUA_PUSH_STRUCT_INT_MEM(L, servers[i], busy);

        lua_rawseti(L, -2, i + 1);
    }
    return 1;
}

DEF_LUA_FUNC(updateServerList)
{
    LUA_FUNCTION func = toluafix_ref_function(L, 1, 0);
    if (func)
    {
        LuaHandler h = createLuaHandler(func);
        fy::GameModule::get<fy::UserManager>()->updateServers([=](fy::UserManager::Result r){
            lua_pushinteger(L, (int)r);
            GetLuaStack()->executeFunctionByHandler(h->getHandler(), 1);
        });
        return 0;
    }
    RET_ARG_ERROR(updateServerList);
}

inline static void registerUserFunctions(lua_State* L)
{
    TOLUA_FUNC(getServers);
    TOLUA_FUNC(updateServerList);
}
