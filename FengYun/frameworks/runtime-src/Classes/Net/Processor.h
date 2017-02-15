/**
 * @file  Processor.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_PROCESSOR_H
#define NET_PROCESSOR_H

#include "netbase.h"
#include "Packet.h"

BEGIN_NS_NET

class Processor
{
public:
    Processor() {}
    virtual ~Processor() {}

    virtual bool accept(int64_t msgId) = 0;

    virtual void process(int64_t msgId, PacketPtr pkg) = 0;

    virtual void onError(int64_t msgId, int error, PacketPtr pkg) = 0;
};

END_NS_NET
#endif /* NET_PROCESSOR_H */
