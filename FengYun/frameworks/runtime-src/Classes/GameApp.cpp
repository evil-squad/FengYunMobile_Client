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

#include "cocos2d.h"

using namespace std;
using namespace std::chrono;

BEGIN_NS_FY

GameApp* GameApp::s_instance = nullptr;

struct GameApp::PrivateData
{
    int adjustSystemTime;
    steady_clock::time_point startTime;

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

}

void GameApp::quit()
{
    cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameApp::onPause()
{

}

void GameApp::onResume()
{

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

void GameApp::runInMainThread(const std::function<void ()> &func)
{
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread(func);
}

END_NS_FY
