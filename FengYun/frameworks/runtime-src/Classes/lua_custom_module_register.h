/**
 * @file  lua_custom_module_register.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef LUA_COSTOM_MODULE_REGISTER_H
#define LUA_COSTOM_MODULE_REGISTER_H

#include "base/ccConfig.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "lua/lua_game_bindings.hpp"
#include "lua/auto/lua_gui_auto.hpp"
#include "lua/lua_gui_manual.hpp"
#include "lua/auto/lua_managers_auto.hpp"
#include "lua/lua_managers_manual.hpp"

static int lua_custom_module_register(lua_State* L)
{
    tolua_beginmodule(L, nullptr);

    register_all_gui(L);
    register_all_gui_manual(L);

    register_all_managers(L);
    register_all_managers_manual(L);

    register_all_game_bindings(L);

    tolua_endmodule(L);

    return 0;
}


#endif /* LUA_COSTOM_MODULE_REGISTER_H */
