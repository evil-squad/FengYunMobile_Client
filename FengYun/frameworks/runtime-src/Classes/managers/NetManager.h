/**
 * @file  NetManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/13.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NETMANAGER_H
#define NETMANAGER_H

#include <functional>
#include "Net/Timer.h"
#include "gamebase.h"
#include "Net/GameConnection.h"
#include "Net/Decoder.h"
#include "Net/Encoder.h"
#include "GameModule.h"

#define GAME_MSG_ID(modId, cmdId) (modId << 8 | cmdId)

BEGIN_NS_FY

class NetManager : public GameModule
{
public:
    class Listener
    {
    public:
        virtual ~Listener() {}

        virtual void onConnected(const std::string& name) = 0;
        virtual void onDisconnected(const std::string& name) = 0;
    };

    struct PrivateData;

    NetManager();
    ~NetManager();

    void connect(const std::string& name, const std::string& ip, unsigned short port, const std::function<void(bool)>&cb);
    void disconnect(const std::string& name);
    void setLostCallback(const std::function<void()>& cb);

    net::GameConnection* getGameConnection();

    void registerListener(Listener* listener);
    void unregisterListener(Listener* listener);

    net::Timer* createTimer();

    void getJson(const std::string& url, const std::function<void(bool succ, const std::string& respStr)>& cb)
    { getJson(url, 0, cb); }

    void getJson(const std::string& url, int timeout, const std::function<void(bool succ, const std::string& respStr)>& cb);

private:
    PrivateData* _data;
};

static const int SEND_HEAD_SIZE = 2 + 2 + 8;

class GamePacketSendHelper
{
public:
    inline GamePacketSendHelper(int64_t msgId, int pktSize)
        : _msgId(msgId)
        , _conn(GameModule::get<NetManager>()->getGameConnection())
        , _pkt(net::PacketCache::makePacket(pktSize + SEND_HEAD_SIZE))
        , _encoder(_pkt->buffer())
    {
        _encoder.writeUInt16(pktSize + SEND_HEAD_SIZE);
        _encoder.writeUInt8(0);
        _encoder.writeUInt8(0);
        _encoder.writeVarInt32((msgId >> 32) & 0xFFFFFFFF);
        _encoder.writeVarInt32(msgId & 0xFFFFFFFF);
    }

    inline ~GamePacketSendHelper()
    {
        if (_conn == nullptr) return;

        if (_pkt->size() > _encoder.offset())
        {
            _encoder.writeHeadLenght(_encoder.offset());
            _conn->send(_msgId, net::PacketCache::makeSlice(_pkt, 0, _encoder.offset()));
        }
        else
        {
            _conn->send(_msgId, _pkt);
        }
    }

    inline net::BasicEncoder& getEncoder() { return _encoder; }

private:
    int64_t _msgId;
    net::GameConnection* _conn;
    net::PacketPtr _pkt;
    net::BasicEncoder _encoder;
};

class GameRPCSendHelper
{
public:
    inline GameRPCSendHelper(int64_t msgId, int pktSize)
        : _conn(GameModule::get<NetManager>()->getGameConnection())
        , _req(net::RPCRequest::create())
        , _pkt(net::PacketCache::makePacket(pktSize + SEND_HEAD_SIZE))
        , _encoder(_pkt->buffer())
    {
        _encoder.writeUInt16(pktSize + SEND_HEAD_SIZE);
        _encoder.writeUInt8(0);
        _encoder.writeUInt8(0);
        _encoder.writeVarInt32((msgId >> 32) & 0xFFFFFFFF);
        _encoder.writeVarInt32(msgId & 0xFFFFFFFF);
        _req->setMsgId(msgId);
    }

    inline ~GameRPCSendHelper()
    {
        if (_pkt->size() > _encoder.offset())
        {
            _req->setPacket(net::PacketCache::makeSlice(_pkt, 0, _encoder.offset()));
        }
        else
        {
            _req->setPacket(_pkt);
        }
        _conn->sendRPC(_req);
    }

    inline net::BasicEncoder& getEncoder() { return _encoder; }

    inline void setCallback(const std::function<void(int error, const net::PacketPtr& pkt)>& cb)
    {
        _req->setCallback(cb);
    }

    inline void setCancelCallback(const std::function<void()>& cb)
    {
        _req->setCancelCallback(cb);
    }

private:
    net::GameConnection* _conn;
    net::RPCRequest* _req;
    net::PacketPtr _pkt;
    net::BasicEncoder _encoder;
};

END_NS_FY
#endif /* NETMANAGER_H */
