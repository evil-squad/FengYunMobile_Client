/**
 * @file  HeartBeatProcess.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/16.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef HEARTBEATPROCESS_H
#define HEARTBEATPROCESS_H

#include "gamebase.h"

BEGIN_NS_FY

class HeartBeatProcess
{
public:
    HeartBeatProcess();
    ~HeartBeatProcess();

    void resetTime();
    void setDelayTime(float time);
    void setOverTime(float time);
    void setUnsTableTime(float time);
    void recvHeartPacket();

    void start();
    void stop();

private:
    bool running;
    float delayTime;
    float currDelayTime;
    float sendTime;
    bool isStartClock;
    float overTime;

    void update(float time);
    void sendHeartBeatPkt();
};

END_NS_FY
#endif /* HEARTBEATPROCESS_H */
