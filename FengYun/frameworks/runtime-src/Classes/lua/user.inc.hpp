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

DEF_LUA_FUNC(connectServer)
{
    int serverId;
    bool ok = true;
    ok &= luaval_to_int32(L, 1, &serverId);
    LUA_FUNCTION func = toluafix_ref_function(L, 2, 0);
    if (ok && func)
    {
        LuaHandler h = createLuaHandler(func);
        fy::GameModule::get<fy::UserManager>()->connectServer(serverId, [=](fy::UserManager::Result r){
            GetLuaStack()->pushInt((int)r);
            GetLuaStack()->executeFunctionByHandler(h->getHandler(), 1);
        });
        return 0;
    }
    RET_ARG_ERROR(connectServer);
}

DEF_LUA_FUNC(createUser)
{
    std::string name;
    std::string password;
    bool ok = true;
    ok &= luaval_to_std_string(L, 1, &name);
    ok &= luaval_to_std_string(L, 2, &password);
    LUA_FUNCTION func = toluafix_ref_function(L, 3, 0);
    if (ok && func)
    {
        LuaHandler h = createLuaHandler(func);
        fy::GameModule::get<fy::UserManager>()->createUser(name, password, [=](fy::UserManager::Result r){
            GetLuaStack()->pushInt((int)r);
            GetLuaStack()->executeFunctionByHandler(h->getHandler(), 1);
        });
        return 0;
    }
    RET_ARG_ERROR(createUser);
}

DEF_LUA_FUNC(createRole)
{
    std::string name;
    int job;
    bool ok = true;
    ok &= luaval_to_std_string(L, 1, &name);
    ok &= luaval_to_int32(L, 2, &job);
    LUA_FUNCTION func = toluafix_ref_function(L, 3, 0);
    if (ok && func)
    {
        LuaHandler h = createLuaHandler(func);
        fy::GameModule::get<fy::UserManager>()->createRole(name, (fy::RoleJob)job, [=](fy::UserManager::Result r){
            GetLuaStack()->pushInt((int)r);
            GetLuaStack()->executeFunctionByHandler(h->getHandler(), 1);
        });
        return 0;
    }
    RET_ARG_ERROR(createRole);
}

DEF_LUA_FUNC(setTestUser)
{
    std::string name;
    bool ok = true;
    ok &= luaval_to_std_string(L, 1, &name);
    if (ok)
    {
        fy::GameModule::get<fy::UserManager>()->setTestUser(name);
        return 0;
    }
    RET_ARG_ERROR(setTestUser);
}

inline static void registerUserFunctions(lua_State* L)
{
    TOLUA_FUNC(getServers);
    TOLUA_FUNC(updateServerList);
    TOLUA_FUNC(connectServer);
    TOLUA_FUNC(createUser);
    TOLUA_FUNC(setTestUser);
    TOLUA_FUNC(createRole);
}
