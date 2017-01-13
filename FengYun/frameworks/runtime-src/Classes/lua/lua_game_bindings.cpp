/**
 * @file  lua_game_bindings.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "lua_game_bindings.hpp"
#include "input.inc.hpp"

int register_all_game_bindings(lua_State* L)
{
    tolua_module(L, "game", 0);
    tolua_beginmodule(L, "game");

    registerInputFunctions(L);

    tolua_endmodule(L);
    return 0;
}
