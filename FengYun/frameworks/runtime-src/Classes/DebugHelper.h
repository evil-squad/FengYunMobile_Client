/**
 * @file  DebugHelper.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 10/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef DEBUGHELPER_H
#define DEBUGHELPER_H

#include "cocos2d.h"

class DebugHelper
{
public:
    static void debugBreak()
    {
        int i = 0;
        i ++;
    }
};

#define ENABLE_DEBUG_LOG

#define DBG_ASSERT(cond, msg) CCASSERT(cond, msg)

#ifdef ENABLE_DEBUG_LOG
#define DBG_LOG(...) CCLOG(__VA_ARGS__)
#else
#define DBG_LOG(...)
#endif

#endif /* DEBUGHELPER_H */
