/**
 * @file  Types.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/13.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_TYPES_H
#define NET_TYPES_H

#include "netbase.h"
#include "buffer.h"

BEGIN_NS_NET

enum class ErrorCode
{
    NONE = 0,
    BUSY,
    UNKNOWN
};

END_NS_NET
#endif /* NET_TYPES_H */
