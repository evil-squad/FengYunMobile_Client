/**
 * @file  lua_managers_manual.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 16/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
 */

#ifndef LUA_MANAGERS_MANUAL_H
#define LUA_MANAGERS_MANUAL_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_managers_manual(lua_State* tolua_S);

#endif /* LUA_MANAGERS_MANUAL_H */
