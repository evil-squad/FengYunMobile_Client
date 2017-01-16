#include "lua_gui_auto.hpp"
#include "GUI.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_gui_TopLevelNode_close(lua_State* tolua_S)
{
    int argc = 0;
    gui::TopLevelNode* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gui.TopLevelNode",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gui::TopLevelNode*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_gui_TopLevelNode_close'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->close();
        return 0;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->close(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "close",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_TopLevelNode_close'.",&tolua_err);
#endif

    return 0;
}
static int lua_gui_TopLevelNode_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (TopLevelNode)");
    return 0;
}

int lua_register_gui_TopLevelNode(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"gui.TopLevelNode");
    tolua_cclass(tolua_S,"TopLevelNode","gui.TopLevelNode","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"TopLevelNode");
        tolua_function(tolua_S,"close",lua_gui_TopLevelNode_close);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(gui::TopLevelNode).name();
    g_luaType[typeName] = "gui.TopLevelNode";
    g_typeCast["TopLevelNode"] = "gui.TopLevelNode";
    return 1;
}

int lua_gui_Layer_closeAll(lua_State* tolua_S)
{
    int argc = 0;
    gui::Layer* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gui.Layer",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gui::Layer*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_gui_Layer_closeAll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->closeAll();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "closeAll",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Layer_closeAll'.",&tolua_err);
#endif

    return 0;
}
int lua_gui_Layer_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"gui.Layer",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        gui::Layer* ret = gui::Layer::create();
        object_to_luaval<gui::Layer>(tolua_S, "gui.Layer",(gui::Layer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Layer_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_gui_Layer_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Layer)");
    return 0;
}

int lua_register_gui_Layer(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"gui.Layer");
    tolua_cclass(tolua_S,"Layer","gui.Layer","cc.Layer",nullptr);

    tolua_beginmodule(tolua_S,"Layer");
        tolua_function(tolua_S,"closeAll",lua_gui_Layer_closeAll);
        tolua_function(tolua_S,"create", lua_gui_Layer_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(gui::Layer).name();
    g_luaType[typeName] = "gui.Layer";
    g_typeCast["Layer"] = "gui.Layer";
    return 1;
}

int lua_gui_Window_setAutoFit(lua_State* tolua_S)
{
    int argc = 0;
    gui::Window* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gui.Window",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gui::Window*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_gui_Window_setAutoFit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setAutoFit(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAutoFit",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Window_setAutoFit'.",&tolua_err);
#endif

    return 0;
}
int lua_gui_Window_isAutoFit(lua_State* tolua_S)
{
    int argc = 0;
    gui::Window* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"gui.Window",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (gui::Window*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_gui_Window_isAutoFit'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isAutoFit();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isAutoFit",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Window_isAutoFit'.",&tolua_err);
#endif

    return 0;
}
int lua_gui_Window_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"gui.Window",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 5)
        {
            gui::Window::Type arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3);
            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4);
            if (!ok) { break; }
            gui::Window* ret = gui::Window::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<gui::Window>(tolua_S, "gui.Window",(gui::Window*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 3)
        {
            gui::Window::Type arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            gui::Window* ret = gui::Window::create(arg0, arg1, arg2);
            object_to_luaval<gui::Window>(tolua_S, "gui.Window",(gui::Window*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Window_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_gui_Window_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Window)");
    return 0;
}

int lua_register_gui_Window(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"gui.Window");
    tolua_cclass(tolua_S,"Window","gui.Window","gui.TopLevelNode",nullptr);

    tolua_beginmodule(tolua_S,"Window");
        tolua_function(tolua_S,"setAutoFit",lua_gui_Window_setAutoFit);
        tolua_function(tolua_S,"isAutoFit",lua_gui_Window_isAutoFit);
        tolua_function(tolua_S,"create", lua_gui_Window_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(gui::Window).name();
    g_luaType[typeName] = "gui.Window";
    g_typeCast["Window"] = "gui.Window";
    return 1;
}

int lua_gui_Panel_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"gui.Panel",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 3)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            gui::Panel* ret = gui::Panel::create(arg0, arg1, arg2);
            object_to_luaval<gui::Panel>(tolua_S, "gui.Panel",(gui::Panel*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 2)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            gui::Panel* ret = gui::Panel::create(arg0, arg1);
            object_to_luaval<gui::Panel>(tolua_S, "gui.Panel",(gui::Panel*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 4)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3);
            if (!ok) { break; }
            gui::Panel* ret = gui::Panel::create(arg0, arg1, arg2, arg3);
            object_to_luaval<gui::Panel>(tolua_S, "gui.Panel",(gui::Panel*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 5)
        {
            double arg0;
            ok &= luaval_to_number(tolua_S, 2,&arg0);
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1);
            if (!ok) { break; }
            double arg2;
            ok &= luaval_to_number(tolua_S, 4,&arg2);
            if (!ok) { break; }
            double arg3;
            ok &= luaval_to_number(tolua_S, 5,&arg3);
            if (!ok) { break; }
            double arg4;
            ok &= luaval_to_number(tolua_S, 6,&arg4);
            if (!ok) { break; }
            gui::Panel* ret = gui::Panel::create(arg0, arg1, arg2, arg3, arg4);
            object_to_luaval<gui::Panel>(tolua_S, "gui.Panel",(gui::Panel*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d", "create",argc, 5);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Panel_create'.",&tolua_err);
#endif
    return 0;
}
int lua_gui_Panel_setInitialScale(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"gui.Panel",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        gui::Panel::setInitialScale(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "setInitialScale",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_gui_Panel_setInitialScale'.",&tolua_err);
#endif
    return 0;
}
static int lua_gui_Panel_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Panel)");
    return 0;
}

int lua_register_gui_Panel(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"gui.Panel");
    tolua_cclass(tolua_S,"Panel","gui.Panel","gui.TopLevelNode",nullptr);

    tolua_beginmodule(tolua_S,"Panel");
        tolua_function(tolua_S,"create", lua_gui_Panel_create);
        tolua_function(tolua_S,"setInitialScale", lua_gui_Panel_setInitialScale);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(gui::Panel).name();
    g_luaType[typeName] = "gui.Panel";
    g_typeCast["Panel"] = "gui.Panel";
    return 1;
}
TOLUA_API int register_all_gui(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"gui",0);
	tolua_beginmodule(tolua_S,"gui");

	lua_register_gui_Layer(tolua_S);
	lua_register_gui_TopLevelNode(tolua_S);
	lua_register_gui_Window(tolua_S);
	lua_register_gui_Panel(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

