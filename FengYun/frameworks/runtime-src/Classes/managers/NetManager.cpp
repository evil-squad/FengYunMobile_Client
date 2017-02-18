/**
 * @file  NetManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/13.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include <queue>
#include <functional>

#include "network/HttpClient.h"

#define ASIO_STANDALONE 1
#include "asio.hpp"

#include "NetManager.h"
#include <thread>

#include "DebugHelper.h"
#include "GameApp.h"
#include "cocos2d.h"

#include "HeartBeatProcess.h"

using asio::ip::tcp;

using namespace cocos2d::network;

BEGIN_NS_FY

#include "Net/TcpConnection.ipp"
#include "Net/Timer.ipp"

struct NetManager::PrivateData
{
    std::thread thread;
    asio::io_service io;

    net::GameConnection* gameConnection;
    std::function<void()> lostCallback;
    std::vector<Listener*> listeners;

    HeartBeatProcess heartBeat;
    asio::io_service::work* work;

    PrivateData() : gameConnection(nullptr), work(nullptr)
    {
        work = new asio::io_service::work(io);
        thread = std::thread([this]{
            io.run();
        });
    }

    ~PrivateData()
    {
        if (gameConnection) delete gameConnection;
        delete work;
        if (thread.joinable()) thread.join();
    }

    void addListener(Listener* l)
    {
        listeners.push_back(l);
    }

    void removeListener(Listener* l)
    {
        auto iter = std::find(listeners.begin(), listeners.end(), l);
        if (iter != listeners.end()) listeners.erase(iter);
    }
};

NetManager::NetManager()
{
    _data = new PrivateData();
}

NetManager::~NetManager()
{
    delete _data;
}

void NetManager::setLostCallback(const std::function<void()>& cb)
{
    _data->lostCallback = cb;
}

void NetManager::connect(const std::string &name, const std::string &ip, unsigned short port, const std::function<void (bool)> &cb)
{
    if (name == "GAME_SERVER")
    {
        auto conn = new TcpConnection(_data->io);

        auto endpoint = asio::ip::tcp::endpoint(asio::ip::address::from_string(ip), port);
        conn->getSocket().async_connect(endpoint, [this, conn, cb](const asio::error_code& ec){
            if (ec)
            {
                conn->destroy();
                GameApp::runInMainThread([=]{
                    cb(false);
                });
                return ;
            }

            conn->getSocket().non_blocking(true);
            conn->getSocket().set_option(asio::ip::tcp::no_delay(true));
            auto gconn = new net::GameConnection(conn);
            _data->gameConnection = gconn;
            _data->gameConnection->setLostCallback([=] {
                GameApp::runInMainThread([=]{
                    if (_data->gameConnection != gconn) return ;
                    disconnect("GAME_SERVER");
                    auto cb = _data->lostCallback;
                    if (cb) cb();
                });
            });

            _data->heartBeat.setDelayTime(10);
            _data->heartBeat.setOverTime(10);
            _data->heartBeat.start();
            GameApp::runInMainThread([=]{
                for (auto l: _data->listeners) l->onConnected("GAME_SERVER");

                gconn->start();
                cocos2d::Director::getInstance()->getScheduler()->schedule([gconn](float dt){
                    gconn->dispatchAll();
                }, this, 0, false, "game_conn_dispatch");
                cb(true);
            });
        });
    }
}

void NetManager::disconnect(const std::string &name)
{
    if (name == "GAME_SERVER")
    {
        if (_data->gameConnection)
        {
            cocos2d::Director::getInstance()->getScheduler()->unschedule("game_conn_dispatch", this);

            for (auto l : _data->listeners)
            {
                l->onDisconnected("GAME_SERVER");
            }

            _data->heartBeat.stop();

            delete _data->gameConnection;
            _data->gameConnection = nullptr;
        }
    }
}

net::GameConnection* NetManager::getGameConnection()
{
    return _data->gameConnection;
}

void NetManager::registerListener(fy::NetManager::Listener *listener)
{
    _data->addListener(listener);
}

void NetManager::unregisterListener(fy::NetManager::Listener *listener)
{
    _data->removeListener(listener);
}

net::Timer* NetManager::createTimer()
{
    return new Timer(_data->io);
}

HttpRequest* createJsonRequest(const std::string& url, const std::string& postStr)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(url);

    if (postStr.empty())
    {
        request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
    }
    else
    {
        request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
        request->setRequestData(postStr.c_str(), postStr.size() + 1);
    }

    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request->setHeaders(headers);

    return request;
}

void onReceiveJson(HttpClient* client, HttpResponse* response, std::function<void(bool succ, const std::string& respStr)>& callback)
{
    auto req = response->getHttpRequest();
    if (req->getUserData() == (void*)1)
        return;
    req->setUserData((void*)2);

    if (!response)
    {
        callback(false, "no response");
        return ;
    }

    if (!response->isSucceed())
    {
        callback(false, std::string(response->getErrorBuffer()));
        return;
    }

    std::vector<char>* buffer = response->getResponseData();
    callback(true, std::string(buffer->begin(), buffer->end()));
}

void NetManager::getJson(const std::string &url, int timeout, const std::function<void (bool, const std::string &)> &cb)
{
    HttpRequest* req = createJsonRequest(url, "");
    if (timeout)
    {
        req->retain();
        cocos2d::Director::getInstance()->getScheduler()->schedule([=](float dt){
            if (req->getUserData() == nullptr)
            {
                req->setUserData((void*)1);
                cb(false, "time out");
            }
            req->release();
        }, req, 0, 0, timeout / 1000.0f, false, cocos2d::StringUtils::format("timeout_function %p", req));
    }
    req->setResponseCallback(std::bind(onReceiveJson, std::placeholders::_1, std::placeholders::_2, cb));
    HttpClient::getInstance()->sendImmediate(req);
    req->release();
}

END_NS_FY
