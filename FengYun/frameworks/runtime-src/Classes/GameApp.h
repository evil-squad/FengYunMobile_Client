/**
 * @file  GameApp.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "gamebase.h"
#include <functional>
#include <cstdint>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

BEGIN_NS_FY

class GameApp
{
public:
    typedef std::function<void()> EventHandler;

    static GameApp* getInstance();
    static void destroyInstance();

    void onStart();
    void onPause();
    void onResume();

    void quit();

    int getDpi();

    float getTime();

    unsigned int getCurrentFrame();
    void adjustTime(std::uint64_t time);
    long getSystemTime();

    static void runInMainThread(const std::function<void()>& func);

private:
    struct PrivateData;

private:
    GameApp();
    ~GameApp();

    void onRelease();

    PrivateData* _data;

    static GameApp* s_instance;
};

END_NS_FY

#endif /* GAMEAPP_H */
