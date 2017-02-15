/**
 * @file  GameConnection.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NET_GAMECONNECTION_H
#define NET_GAMECONNECTION_H

#include "netbase.h"
#include "Connection.h"
#include "Net/Processor.h"
#include "Net/Packet.h"

BEGIN_NS_NET

class RPCRequest
{
public:
    static RPCRequest* create();
    static void release(RPCRequest* req);

    void setMsgId(int64_t msgId) { _msgId = msgId; }
    int64_t getMsgId() const { return _msgId; }

    void setPacket(const PacketPtr& pkg) { _pkg = pkg; }
    const PacketPtr& getPacket() const { return _pkg; }

    void setCallback(const std::function<void(int error, const PacketPtr& pkg)>& cb) { _cb = cb; }
    void setCancelCallback(const std::function<void()>& cb) { _cancelCb = cb; }

    const std::function<void(int error, const PacketPtr& pkg)>& getCallback() const { return _cb; }
    const std::function<void()>& getCancelCallback() const { return _cancelCb; }

private:
    RPCRequest()
        : _msgId(0)
        , _pkg(nullptr)
        , _cb(nullptr)
        , _cancelCb(nullptr)
    {}

    int64_t _msgId;
    PacketPtr _pkg;
    std::function<void(int error, const PacketPtr& pkg)> _cb;
    std::function<void()> _cancelCb;
};

class GameConnection
{
public:
    struct PrivateData;

    GameConnection(Connection* conn);
    ~GameConnection();

    void start();

    void adjustTime(float clientTime, float serverTime);

    void registerProcessor(Processor* p);
    void unregisterProcessor(Processor* p);

    void setLostCallback(const std::function<void()>& cb);

    void send(int64_t msgId, const PacketPtr& pkg);

    void sendRPC(RPCRequest* req);

    void dispatchAll();

private:
    PrivateData* _data;

    void recvNextPacket();
    void sendNextPacket();
};

END_NS_NET
#endif /* NET_GAMECONNECTION_H */
