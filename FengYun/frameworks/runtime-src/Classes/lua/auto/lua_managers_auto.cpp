#include "lua_managers_auto.hpp"
#include "UIManager.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

using namespace fy;
int lua_managers_UIManager_getUILayer(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_managers_UIManager_getUILayer'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 0) {
            const gui::Layer* ret = cobj->getUILayer();
            object_to_luaval<gui::Layer>(tolua_S, "gui.Layer",(gui::Layer*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            gui::Layer* ret = cobj->getUILayer();
            object_to_luaval<gui::Layer>(tolua_S, "gui.Layer",(gui::Layer*)ret);
            return 1;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getUILayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_managers_UIManager_getUILayer'.",&tolua_err);
#endif

    return 0;
}
int lua_managers_UIManager_getUIRect(lua_State* tolua_S)
{
    int argc = 0;
    UIManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"UIManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (UIManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_managers_UIManager_getUIRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const cocos2d::Rect& ret = cobj->getUIRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getUIRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_managers_UIManager_getUIRect'.",&tolua_err);
#endif

    return 0;
}
static int lua_managers_UIManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (UIManager)");
    return 0;
}

int lua_register_managers_UIManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"UIManager");
    tolua_cclass(tolua_S,"UIManager","UIManager","",nullptr);

    tolua_beginmodule(tolua_S,"UIManager");
        tolua_function(tolua_S,"getUILayer",lua_managers_UIManager_getUILayer);
        tolua_function(tolua_S,"getUIRect",lua_managers_UIManager_getUIRect);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(UIManager).name();
    g_luaType[typeName] = "UIManager";
    g_typeCast["UIManager"] = "UIManager";
    return 1;
}
TOLUA_API int register_all_managers(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_managers_UIManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

