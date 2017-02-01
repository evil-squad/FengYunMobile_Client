/**
 * @file  GameApp.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GameApp.h"
#include <cstddef>
#include <chrono>
#include <thread>

#include "GameModule.h"

#include "cocos2d.h"
#include "DebugHelper.h"

#include "UIManager.h"
#include "SceneManager.h"
#include "AnimationManager.h"

using namespace std;
using namespace std::chrono;
USING_NS_CC;

BEGIN_NS_FY

template <class T>
static  T* createAndRegisterModule()
{
    T* m = new T();
    GameModule::set<T>(m);
    return m;
}

static void createAndRegisterMudules(std::vector<GameModule*>& modules)
{
    DBG_ASSERT(modules.empty(), "Modules not empty!");
    modules.push_back(createAndRegisterModule<UIManager>());
    modules.push_back(createAndRegisterModule<SceneManager>());
    modules.push_back(createAndRegisterModule<AnimationManager>());
}

GameApp* GameApp::s_instance = nullptr;

struct GameApp::PrivateData
{
    int adjustSystemTime;
    steady_clock::time_point startTime;
    std::unordered_map<std::string, EventHandler> handlers;
    std::vector<GameModule*> modules;

    PrivateData()
    : adjustSystemTime(0)
    , startTime()
    {}
};

GameApp* GameApp::getInstance()
{
    if (s_instance == nullptr)
        s_instance = new GameApp();

    return s_instance;
}

void GameApp::destroyInstance()
{
    if (s_instance)
    {
        s_instance->onRelease();
        delete s_instance;
        s_instance = nullptr;
    }
}

GameApp::GameApp()
{
    _data = new PrivateData();
}

GameApp::~GameApp()
{
    delete _data;
}

void GameApp::onRelease()
{

}

void GameApp::onStart()
{
    _data->startTime = steady_clock::now();

    auto fu = FileUtils::getInstance();
    auto path = getPersistenDataPath();
    if (!fu->isDirectoryExist(path))
        fu->createDirectory(path);

#ifdef ENABLE_DEBUG_FPS
    Director::getInstance()->setDisplayStats(true);
#else
    Director::getInstance()->setDisplayStats(false);
#endif

    fu->addSearchPath("src/");
    fu->addSearchPath("res/");
    fu->addSearchPath("res/default/builtin/");
    fu->addSearchPath("res/default/dynamic/");
    fu->addSearchPath("res/default/config/");

    createAndRegisterMudules(_data->modules);

    for (auto srv : _data->modules)
        srv->onInitialize();

    setEventHandler("start_game", [=]{
        GameModule::get<UIManager>()->initUIRect();
        GameApp::getInstance()->sendEvent("goto_init_ui");
        GameApp::setEventHandler("start_game", nullptr);
    });

    setEventHandler("goto_init_ui", []{
        GameModule::get<SceneManager>()->gotoUIScene("InitialScene", []{
            GameApp::getInstance()->sendEvent("open_init_ui");
        });
        GameApp::getInstance()->setEventHandler("goto_init_ui", nullptr);
    });

    setEventHandler("goto_game_scene", []{
        GameModule::get<SceneManager>()->gotoScene(1);
        GameApp::getInstance()->setEventHandler("goto_game_scene", nullptr);
    });
}

void GameApp::onPause()
{

}

void GameApp::onResume()
{

}

void GameApp::quit()
{
    cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

int GameApp::getDpi()
{
    return cocos2d::Device::getDPI();
}

float GameApp::getTime()
{
    duration<float> seconds = steady_clock::now() - _data->startTime;
    return seconds.count();
}

unsigned int GameApp::getCurrentFrame()
{
    return cocos2d::Director::getInstance()->getTotalFrames();
}

void GameApp::adjustTime(std::uint64_t time)
{
    _data->adjustSystemTime = time - std::time(NULL);
}

long GameApp::getSystemTime()
{
    time_t result = std::time(NULL);
    return result + _data->adjustSystemTime;
}

void GameApp::setEventHandler(const std::string &name, EventHandler handler)
{
    if (handler)
        _data->handlers[name] = handler;
    else
        _data->handlers.erase(name);
}

void GameApp::sendEvent(const std::string &name)
{
    auto iter = _data->handlers.find(name);
    if (iter != _data->handlers.end())
    {
        auto cb = iter->second;
        if (cb) cb();
    }
}

void GameApp::runInMainThread(const std::function<void ()> &func)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(func);
}

std::string GameApp::getPersistenDataPath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS) || (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return FileUtils::getInstance()->getWritablePath();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    return cocos2d::FileUtils::getInstance()->getWritablePath() + ".fengyun/";
#endif
}

void GameApp::loadConfigs(const std::function<void ()> &cb)
{
    if (cb)
        cb();
}

END_NS_FY
