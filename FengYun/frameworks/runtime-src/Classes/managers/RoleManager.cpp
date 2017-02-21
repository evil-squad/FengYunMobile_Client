/**
 * @file  RoleManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/8.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "RoleManager.h"
#include "NetManager.h"
#include "GameConfigLoader.h"

BEGIN_NS_FY

namespace
{
    class WorkImpl : public RoleManager::Work
    {
    public:
        WorkImpl(int* count, const std::function<void()>& cb)
            : _count(count)
            , _cb(cb)
        {
        }

        virtual ~WorkImpl()
        {}

        virtual void markDone() override
        {
            (*_count) --;
            if (*_count == 0)
            {
                _cb();
                delete _count;
            }
            delete this;
        }

    private:
        int* _count;
        std::function<void()> _cb;
    };
}

struct RoleManagerData_t
{
    class Processor;
    class Listener;
    Processor* processor;
    Listener* listener;

    RoleData* playerData;

    std::vector<RoleManager::Listener*> listeners;
    std::function<void()> playerDataCompleteCallback;

    RoleManagerData_t()
    {
        playerData = new RoleData();
    }

    ~RoleManagerData_t()
    {
        if (playerData)
        {
            delete playerData;
            playerData = nullptr;
        }
    }

    void resetPlayerData()
    {
        for (auto l : listeners)
        {
            l->onPlayerDataReset();
        }
    }
};

////////////////TODO: class RoleManagerData_t Processor
class RoleManagerData_t::Processor : public net::Processor
{
public:
    static const int PLAYER_MODID = 1;

    Processor(RoleManagerData_t* data)
    : _data(data)
    {}

private:
    RoleManagerData_t* _data;

    void onInitData(const net::PacketPtr& pkt)
    {
        net::BasicDecoder d(pkt->buffer());

        for (auto l: _data->listeners)
        {
            l->onPlayerDataInit();
        }
    }

    void onSyncComplete()
    {
        int* count = new int(_data->listeners.size());

        for (auto l : _data->listeners)
        {
            RoleManager::Work* w = new WorkImpl(count, [this]{
                auto cb = _data->playerDataCompleteCallback;
                if (cb) cb();
            });

            l->onPlayerDataSync(w);
        }
    }
};

///////////////////TODO: class RoleManagerData_t::Listener
class RoleManagerData_t::Listener : public NetManager::Listener
{
public:
    Listener(RoleManagerData_t* data) : _data(data) {}
    virtual ~Listener() {}

    void onConnected(const std::string& name) override
    {
        if (name != "GAME_SERVER") return;

        GameModule::get<NetManager>()->getGameConnection()->registerProcessor(_data->processor);
    }

    void onDisconnected(const std::string& name) override
    {
        if (name != "GAME_SERVER") return;

        GameModule::get<NetManager>()->getGameConnection()->unregisterProcessor(_data->processor);
    }

private:
    RoleManagerData_t* _data;
};


////////////////TODO: class RoleManger
RoleManager::RoleManager()
{
    _data = new RoleManagerData_t();
}

RoleManager::~RoleManager()
{
    delete _data;
}

void RoleManager::onLoadConfig(fy::GameConfigLoader *loader)
{
    loader->load("hero");
}

void RoleManager::onInitialize()
{

}

void RoleManager::onRelease()
{
    
}

const RoleData* RoleManager::getPlayerData()
{
    return _data->playerData;
}

RoleData* RoleManager::getEditablePlayerData()
{
    return _data->playerData;
}

void RoleManager::registerListener(fy::RoleManager::Listener *listener)
{
    _data->listeners.push_back(listener);
}

void RoleManager::unregisterListener(fy::RoleManager::Listener *listener)
{
    auto iter = std::find(_data->listeners.begin(), _data->listeners.end(), listener);
    if (iter != _data->listeners.end())
        _data->listeners.erase(iter);
}


END_NS_FY
