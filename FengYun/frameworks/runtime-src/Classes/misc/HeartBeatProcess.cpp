/**
 * @file  HeartBeatProcess.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/16.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "HeartBeatProcess.h"
#include "cocos2d.h"
#include "GameModule.h"
#include "NetManager.h"
#include "GameApp.h"

BEGIN_NS_FY

HeartBeatProcess::HeartBeatProcess()
    : delayTime(0.0)
    , running(false)
    , currDelayTime(0)
    , sendTime(0)
    , isStartClock(false)
    , overTime(0)
{
    cocos2d::Director::getInstance()->getScheduler()->schedule(std::bind(&HeartBeatProcess::update, this, std::placeholders::_1), this, 0, false, "heart_beat_process");
}

HeartBeatProcess::~HeartBeatProcess()
{
    cocos2d::Director::getInstance()->getScheduler()->unschedule("heart_beat_process", this);
}

void HeartBeatProcess::recvHeartPacket()
{
    currDelayTime = 0;
    GameApp::runInMainThread([this](){
        
    });
}

void HeartBeatProcess::resetTime()
{
    currDelayTime = 0;
    sendTime = 0;
    isStartClock = false;
}

void HeartBeatProcess::setDelayTime(float time)
{
    delayTime = time;
}

void HeartBeatProcess::setOverTime(float time)
{
    overTime = time;
}

void HeartBeatProcess::start()
{
    running = true;
}

void HeartBeatProcess::stop()
{
    running = false;
    isStartClock = false;
    sendTime = 0;
    currDelayTime = 0;
}

void HeartBeatProcess::sendHeartBeatPkt()
{
    isStartClock = true;
    sendTime = 0;

    return;

    fy::GamePacketSendHelper h(2ul << 32 | 15, 0);
}

void HeartBeatProcess::update(float time)
{
    if (!running) return ;

    if (isStartClock)
    {
        sendTime += time;
        if (sendTime > overTime)
        {
            running = false;
            GameApp::getInstance()->sendEvent("game_connection_losted");
        }
    }
    else
    {
        currDelayTime += time;
        if (currDelayTime > delayTime)
        {
            sendHeartBeatPkt();
        }
    }
}

END_NS_FY
