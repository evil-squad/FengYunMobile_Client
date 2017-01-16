#include "base/ccConfig.h"
#ifndef __managers_h__
#define __managers_h__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

int register_all_managers(lua_State* tolua_S);






#endif // __managers_h__
