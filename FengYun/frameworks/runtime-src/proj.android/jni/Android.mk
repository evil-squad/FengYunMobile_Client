LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dlua_shared

LOCAL_MODULE_FILENAME := libcocos2dlua

FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/ECS/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/FSM/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/GUI/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/Net/*cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/Scenes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/lua/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/lua/auto/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/managers/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/misc/*.cpp)

LOCAL_SRC_FILES := hellolua/main.cpp $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/managers \
					$(LOCAL_PATH)/../../Classes/Scenes \
					$(LOCAL_PATH)/../../Classes/misc \
					$(LOCAL_PATH)/../../Classes/lua


# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END

LOCAL_STATIC_LIBRARIES := cocos2d_lua_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,scripting/lua-bindings/proj.android)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
