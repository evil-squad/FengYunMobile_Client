/**
 * @file  Timer.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_TIMER_H
#define NET_TIMER_H

#include "netbase.h"
#include <functional>
#include "Types.h"

BEGIN_NS_NET

class Timer
{
public:
    Timer() {}
    virtual ~Timer() {}

    virtual void setExpiresTime(int timeInMs) = 0;
    virtual bool isExpires() const = 0;
    virtual void startWait(const std::function<void(net::ErrorCode)>& handler) = 0;
    virtual void destroy() = 0;
};

END_NS_NET
#endif /* NET_TIMER_H */
