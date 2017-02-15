/**
 * @file  GameConnection.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include <vector>
#include <queue>
#include <unordered_map>
#include <mutex>

#include "DebugHelper.h"
#include "GameConnection.h"
#include "GameApp.h"
#include "Decoder.h"
#include "Encoder.h"

#define ENABLE_PACKET_LOG

BEGIN_NS_NET

static const int SEND_HEAD_SIZE = 2 + 2 + 8;

RPCRequest* RPCRequest::create()
{
    return new RPCRequest();
}

void RPCRequest::release(fy::net::RPCRequest *req)
{
    delete req;
}

struct GameConnection::PrivateData
{
    bool valid;
    bool sending;

    float clientStartTime;
    float serverStartTime;

    Connection* conn;

    std::vector<Processor*> processors;

    std::queue<PacketPtr> recvPackets;

    std::queue<std::pair<int64_t, PacketPtr>> sendPackets;

    std::queue<RPCRequest*> rpcRequests;

    std::mutex sendLock;
    std::mutex recvLock;

    std::function<void()> lostCallback;

    unsigned char recvHead[2];
    unsigned char sendHead[SEND_HEAD_SIZE];

    std::unordered_map<int64_t, Processor*> quickDispatchMap;

    PrivateData()
        : valid(false)
        , sending(false)
        , clientStartTime(0)
        , serverStartTime(0)
        , conn(nullptr)
        , lostCallback(nullptr)
    {}

    ~PrivateData()
    {
        while (rpcRequests.size() > 0)
        {
            auto iter = rpcRequests.front();
            auto callback = iter->getCancelCallback();
            if (callback)
                callback();

            RPCRequest::release(iter);
            rpcRequests.pop();
        }

        if (conn)
        {
            conn->destroy();
            conn = nullptr;
        }
    }

    Processor* findProcessor(int64_t msgId)
    {
        auto it = quickDispatchMap.find(msgId);
        if (it != quickDispatchMap.end() && it->second->accept(msgId))
            return it->second;

        for (auto p: processors)
        {
            if (p->accept(msgId))
            {
                quickDispatchMap[msgId] = p;
                return p;
            }
        }
        return nullptr;
    }

    bool checkLost(ErrorCode ec)
    {
        if (ec != ErrorCode::NONE)
        {
            if (valid)
            {
                valid = false;
                DBG_LOG("game conn lost %f ec %d", GameApp::getInstance()->getTime(), (int)ec);
                auto cb = lostCallback;
                if (cb) cb();
            }
        }
        return !valid;
    }

    bool removeRpcRequest(int msgId)
    {
        if (rpcRequests.size() > 0)
        {
            auto req = rpcRequests.front();
            if (req->getMsgId() == msgId)
            {
                rpcRequests.pop();
                RPCRequest::release(req);
                return true;
            }
        }
        return false;
    }
};

GameConnection::GameConnection(Connection* conn)
{
    _data = new PrivateData();
    _data->conn = conn;
    _data->valid = true;
}

GameConnection::~GameConnection()
{
    delete _data;
    _data = nullptr;
}

void GameConnection::setLostCallback(const std::function<void ()> &cb)
{
    _data->lostCallback = cb;
}

void GameConnection::start()
{
    recvNextPacket();
}

void GameConnection::adjustTime(float clientTime, float serverTime)
{
    _data->clientStartTime = clientTime;
    _data->serverStartTime = serverTime;
}

void GameConnection::send(int64_t msgId, const PacketPtr &pkg)
{
    if (!_data->valid) return ;

    bool sending;

    {
        std::lock_guard<std::mutex> g(_data->sendLock);
        _data->sendPackets.push(std::make_pair(msgId, pkg));
        sending = _data->sending;
    }

    if (!sending)
    {
#ifdef ENABLE_PACKET_LOG
        DBG_LOG("game send start");
#endif
        sendNextPacket();
    }
}

void GameConnection::sendRPC(fy::net::RPCRequest *req)
{
    if (!_data->valid) return;
    _data->rpcRequests.push(req);
    this->send(req->getMsgId(), req->getPacket());
}

void GameConnection::registerProcessor(fy::net::Processor *p)
{
    _data->processors.push_back(p);
}

void GameConnection::unregisterProcessor(fy::net::Processor *p)
{
    auto iter = std::find(_data->processors.begin(), _data->processors.end(), p);
    if (iter != _data->processors.end())
        _data->processors.erase(iter);
}

static void dispatch(GameConnection::PrivateData*data, PacketPtr pkt);


void GameConnection::dispatchAll()
{
    PacketPtr pkt = nullptr;
    while (true)
    {
        {
            std::lock_guard<std::mutex> g(_data->recvLock);
            if (_data->recvPackets.empty())
                break;
            pkt = _data->recvPackets.front();
            _data->recvPackets.pop();
        }
        dispatch(_data, pkt);
    }
}

void GameConnection::recvNextPacket()
{
#ifdef ENABLE_PACKET_LOG
    DBG_LOG("Game recv: start [%fs]", GameApp::getInstance()->getTime());
#endif

    _data->conn->recv(buffer(_data->recvHead, 2), [this](ErrorCode ec, std::size_t bytes_transferred){
        if (_data->checkLost(ec)) return;

        int len = BasicDecoder(buffer(_data->recvHead, 2)).readUInt16();
        PacketPtr pkt = PacketCache::makePacket(len);
        float time = GameApp::getInstance()->getTime();

        _data->conn->recv(pkt->buffer(), [this, pkt, time](ErrorCode ec, std::size_t bytes_transferred){
            if (_data->checkLost(ec)) return;

            float curTime = GameApp::getInstance()->getTime();
            BasicDecoder d(pkt->buffer());
            d.skip(8);
            int msgId = d.readUInt16();
#ifdef ENABLE_PACKET_LOG
            DBG_LOG("game recv: complete id [%d, %d][%fs, %fs, %fms]", (msgId >> 8) & 0xFF, msgId & 0xFF, time, curTime, (curTime-time)*1000);
#endif
            {
                std::lock_guard<std::mutex> g(_data->recvLock);
                _data->recvPackets.push(pkt);
            }

            recvNextPacket();
        });
    });
}

static inline void writeSendHead(mutable_buffer buf, float time, int msgId, int size)
{
    BasicEncoder e(buf);
    e.writeUInt16(size + 2 + 8);
    e.writeUInt64(time * 1000);
    e.writeUInt16(msgId);
}

void GameConnection::sendNextPacket()
{
    int64_t msgId;
    PacketPtr pkt;

    {
        std::lock_guard<std::mutex> g(_data->sendLock);

        if (_data->sendPackets.size() == 0)
        {
            _data->sending = false;
#ifdef ENABLE_PACKET_LOG
            DBG_LOG("Game Send Stop");
#endif
            return;
        }

        msgId = _data->sendPackets.front().first;
        pkt = _data->sendPackets.front().second;
        _data->sendPackets.pop();
        _data->sending = true;
    }

    float clientTime = GameApp::getInstance()->getTime();
    float clientDeltaTime = _data->clientStartTime == 0 ? 0 : (clientTime - _data->clientStartTime);
    float serverTime = _data->serverStartTime + clientDeltaTime;

#ifdef ENABLE_PACKET_LOG
    DBG_LOG("game send: id [%lld, %lld] time [%fs, %fs]", (msgId >> 32) & 0xFFFFFFFF, msgId & 0xFFFFFFFF, clientTime, serverTime);
#endif

//    auto headBuf = buffer(_data->sendHead, SEND_HEAD_SIZE);
//    writeSendHead(headBuf, serverTime, msgId, (int)pkt->size());
//    _data->conn->send(headBuf, [this, msgId, pkt, clientTime](ErrorCode ec, std::size_t bytes_transferred){
//        if (_data->checkLost(ec)) return;

        _data->conn->send(pkt->buffer(), [this, msgId, pkt, clientTime](ErrorCode ec, std::size_t bytes_transferred){
            if (_data->checkLost(ec)) return;

            float time = GameApp::getInstance()->getTime();
#ifdef ENABLE_PACKET_LOG
            DBG_LOG("game send: id [%lld, %lld] complete [%fs, %fms]", (msgId >> 32) & 0xFFFFFFFF, msgId & 0xFFFFFFFF, time, (time-clientTime) * 1000);
#endif
            sendNextPacket();
        });
//    });
}

static const int SERVER_PLAYER_MOD_ID = 1;
static const int SERVER_ERROR_CMD_ID = 2;

static inline bool tryToFeedRPC(GameConnection::PrivateData* data, int64_t msgId, int error, const PacketPtr& pkt)
{
    if (data->rpcRequests.size() > 0)
    {
        auto req = data->rpcRequests.front();
        if (req->getMsgId() == msgId)
        {
            data->rpcRequests.pop();
            auto& cb = req->getCallback();
            if (cb) cb(error, pkt);

            RPCRequest::release(req);
            return true;
        }
    }
    return false;
}

void dispatch(GameConnection::PrivateData* data, PacketPtr pkt)
{
    BasicDecoder d(pkt->buffer());
    auto time = d.readUInt64();
    int msgId = d.readUInt16();
    int error = 0;
    PacketPtr dataPkt;
    if (msgId == (SERVER_PLAYER_MOD_ID << 8 | SERVER_ERROR_CMD_ID))
    {
        msgId = d.readUInt16();
        error = d.readUInt16();
        dataPkt = PacketCache::makeSlice(pkt, 6 + 8);
    }
    else
    {
        dataPkt = PacketCache::makeSlice(pkt, 2 + 8);
    }

    float clientTime = GameApp::getInstance()->getTime();
    float serverTime = time / 1000.0;
    float clientDeltaTime = data->clientStartTime == 0 ? 0 : (clientTime - data->clientStartTime);
    float serverDeltaTime = data->serverStartTime == 0 ? 0 : (serverTime - data->serverStartTime);
    float delayInMs = (clientDeltaTime - serverDeltaTime) * 1000;

    if (!tryToFeedRPC(data, msgId, error, dataPkt))
    {
        Processor* p = data->findProcessor(msgId);
        if (p)
        {
            if (error == 0)
            {
                p->process(msgId, dataPkt);
            }
            else
            {
                p->onError(msgId, error, dataPkt);
            }
        }
    }

#ifdef ENABLE_PACKET_LOG
    float processTimeInMs = (GameApp::getInstance()->getTime() - clientTime) * 1000;
    DBG_LOG("game recv: id [%d, %d] error %d time [%fs, %fs, %fms, %fms]", (msgId >> 8) & 0xFF, (msgId) & 0xFF, error, clientTime, serverTime, delayInMs, processTimeInMs);
#endif
}

END_NS_NET
