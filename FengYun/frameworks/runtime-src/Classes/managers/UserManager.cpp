/**
 * @file  UserManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UserManager.h"

#include <ostream>
#include <fstream>

#include "cocos2d.h"

#include "GameApp.h"
#include "GameConfigLoader.h"

#include "RoleManager.h"

#include "NetManager.h"
#include "Net/Decoder.h"
#include "Net/Encoder.h"

#include "json/document.h"

#include "DebugHelper.h"

#define SERVER_LIST_FILE_NAME "servers.json"
#define SERVER_MANIFEST_NAME "servers.manifest"

USING_NS_CC;

BEGIN_NS_FY

struct Account
{
    std::string name, password;
    bool isAutoLogin;
    Account(const std::string& name_, const std::string& password_, bool isAuto_)
    {
        name = name_;
        password = password_;
        isAutoLogin = isAuto_;
    }
};

static void loadSavedAccounts(std::vector<Account>& _accounts, std::vector<Account>& _savedAccount);
static void saveSavedAccounts(std::vector<Account>& _accounts, std::vector<Account>& _savedAccount);

static unsigned char* parseIpFromString(const char* str);

///////////TODO: class UserManager PrivateData
struct UserManager::PrivateData
{
    struct Manifest
    {
        std::string serverListUrl;
        std::string localServerListUrl;
    };

    Manifest _curManifest;

    int _serverId;

    ResultCallback _serversCallback;

    std::vector<Account> _accounts;

    std::vector<ServerEntry> _servers;

    std::vector<Account> _savedAccounts;

    ResultCallback _loginCallback;
    ResultCallback _logoutCallback;

    Processor* _processor;
    Listener* _listener;

    PrivateData()
        : _serverId(0)
    {}

    ~PrivateData()
    {}

    void resetData()
    {

    }

    void updateServers(ResultCallback callback)
    {
        _serversCallback = callback;
        GameModule::get<NetManager>()->getJson(_curManifest.serverListUrl + SERVER_LIST_FILE_NAME, 1500, [this](bool succ, const std::string& respStr){
            if (succ)
            {
                onReceiveServerList(succ, respStr);
            }
            else
            {

            }

        });
    }

    bool parseServerList(const std::string& str)
    {
        rapidjson::Document doc;
        doc.Parse<0>(str.c_str());
        if (doc.HasParseError())
        {
            DBG_LOG("Error '%u' on parse %s", doc.GetParseError(), str.c_str());
            return false;
        }

        int count = doc.Size();
        _servers.clear();
        for (int i = 0; i < count; ++ i)
        {
            auto& e = doc[i];
            _servers.push_back(ServerEntry(
                    e["id"].GetInt(),
                    e["name"].GetString(),
                    e["busy"].GetInt(),
                    parseIpFromString(e["ip"].GetString()),
                    e["port"].GetInt()));
        }
        return true;
    }

    void onReceiveServerList(bool succ, const std::string& str)
    {
        if (succ)
        {
            if (parseServerList(str))
            {
                if (_serversCallback)
                    _serversCallback(Result::SUCCESS);
            }
            else
            {
                if (_serversCallback)
                    _serversCallback(Result::UNKNOWN_ERROR);
            }
        }
        else
        {
            if (_serversCallback)
                _serversCallback(Result::NETWORK_ERROR);
        }

        _serversCallback = nullptr;
    }
};

///////////////TODO: class UserManager Processor
class UserManager::Processor : public net::Processor
{
public:
    Processor(PrivateData* data)
        : _data(data)
        , _loginCallback(nullptr)
        , _createRoleCallback(nullptr)
    {}

    virtual ~Processor() {}

    bool accept(int64_t msgId) override
    {
        return true;
    }

    void process(int64_t msgId, net::PacketPtr pkt) override
    {

    }

    void onError(int64_t msgId, int error, net::PacketPtr pkt) override
    {

    }

private:
    PrivateData* _data;

    std::function<void(Result)> _loginCallback;
    std::function<void(Result)> _createRoleCallback;
};

/////////////////TODO: class UserManager Listener
class UserManager::Listener : public NetManager::Listener, public RoleManager::Listener
{
public:
    Listener(UserManager* mgr) : _mgr(mgr)
    {}
    virtual ~Listener() {}

    void onConnected(const std::string& name) override
    {
        if (name != "GAME_SERVER") return;

        GameModule::get<NetManager>()->getGameConnection()->registerProcessor(_mgr->_data->_processor);
    }

    void onDisconnected(const std::string& name) override
    {
        if (name != "GAME_SERVER") return;

        GameModule::get<NetManager>()->getGameConnection()->unregisterProcessor(_mgr->_data->_processor);
    }

    void onPlayerDataInit() override
    {

    }

    void onPlayerDataSync(RoleManager::Work* work) override
    {
        work->markDone();
    }

    void onPlayerDataReset() override
    {
        _mgr->_data->resetData();
    }

private:
    UserManager* _mgr;
};

/////////////////TODO: class UserManager
UserManager::UserManager()
{
    _data = new PrivateData();
    _data->_processor = new Processor(_data);
    _data->_listener = new Listener(this);
}

UserManager::~UserManager()
{
    delete _data->_processor;
    delete _data->_listener;
    delete _data;
}

void UserManager::onLoadConfig(fy::GameConfigLoader *loader)
{

}

static void loadServersManifest(UserManager::PrivateData::Manifest& data)
{
    std::string path = "res/"  SERVER_MANIFEST_NAME;

    if (!FileUtils::getInstance()->isFileExist(path))
    {
        DBG_LOG("%s file not fount!", path.c_str());
        DBG_ASSERT(false, "File not Found");
        return;
    }

    std::string str = FileUtils::getInstance()->getStringFromFile(path);

    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        DBG_LOG("Error '%u' on Parse '%s' ", doc.GetParseError(), path.c_str());
        return;
    }

    data.serverListUrl = doc["serverListUrl"].GetString();
    data.localServerListUrl = doc["localServerListUrl"].GetString();
}

void UserManager::onInitialize()
{
    GameModule::get<NetManager>()->registerListener(_data->_listener);
    GameModule::get<RoleManager>()->registerListener(_data->_listener);
}

void UserManager::onRelease()
{
    GameModule::get<NetManager>()->unregisterListener(_data->_listener);
    GameModule::get<RoleManager>()->unregisterListener(_data->_listener);
}

void UserManager::updateServers(const ResultCallback &callback)
{
    _data->updateServers(callback);
}

const std::vector<UserManager::ServerEntry>& UserManager::getServers()
{
    return _data->_servers;
}

unsigned char* parseIpFromString(const char* str)
{
    static unsigned char ip[4] = { 0 };
    size_t index = 0;

    ip[index] = 0;
    while (*str) {
        if (isdigit((unsigned char)*str)) {
            ip[index] *= 10;
            ip[index] += *str - '0';
        } else {
            index++;
            ip[index] = 0;
        }
        str++;
    }

    return ip;
}

END_NS_FY
