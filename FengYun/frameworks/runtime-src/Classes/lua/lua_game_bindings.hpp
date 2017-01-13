/**
 * @file  lua_game_bindings.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef LUA_GAME_BINDINGS_HPP
#define LUA_GAME_BINDINGS_HPP

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_game_bindings(lua_State* tolua_S);

#endif /* LUA_GAME_BINDINGS_HPP */
