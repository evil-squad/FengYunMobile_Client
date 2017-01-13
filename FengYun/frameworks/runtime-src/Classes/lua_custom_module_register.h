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


static int lua_custom_module_register(lua_State* L)
{
    tolua_beginmodule(L, nullptr);

    tolua_endmodule(L);

    return 0;
}


#endif /* LUA_COSTOM_MODULE_REGISTER_H */
