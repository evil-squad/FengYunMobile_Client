/**
 * @file  Connection.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/13.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_CONNECTION_H
#define NET_CONNECTION_H

#include "netbase.h"
#include <functional>
#include "Types.h"

BEGIN_NS_NET

class Connection
{
public:
    typedef std::function<void(ErrorCode ec, std::size_t  bytes_transferred)> Handler;

    virtual bool isOpen() = 0;

    virtual void recv(mutable_buffer buf, const Handler& handler) = 0;
    virtual void send(const_buffer buf, const Handler& handler) = 0;

    virtual void destroy() = 0;

protected:
    Connection() {}
    virtual ~Connection() {}
};

END_NS_NET
#endif /* NET_CONNECTION_H */
