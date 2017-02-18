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

#include "hero.pb.h"
#include "NetModDefine.h"

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

static bool loadUserData(UserInfo& user);
static void saveUserData(UserInfo& user);

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
    UserInfo curUser;

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
//        , curUser(nullptr)
    {}

    ~PrivateData()
    {
//        if (curUser)
//        {
//            delete curUser;
//            curUser = nullptr;
//        }
    }

    void resetData()
    {
//        if (curUser)
//        {
//            delete curUser;
//            curUser = nullptr;
//        }
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
        int modId = (msgId >> 32) & 0xFFFFFFFF;
        if ( modId == MISC_MODULE_ID || modId == LOGIN_MOD_ID ) return true;
        return false;
    }

    void process(int64_t msgId, net::PacketPtr pkt) override
    {
        int modId = (msgId >> 32) & 0xFFFFFFFF;
        int cmdId = msgId & 0xFFFFFFFF;

        switch (cmdId)
        {
            case 16:
                DBG_LOG("Pong respone");
                break;
            case 0:
            {
                if (modId == LOGIN_MOD_ID)
                {
                    net::BasicDecoder d(pkt->buffer());
                    int replayCode = d.readUInt8();
                    DBG_LOG("relay code----->%d", replayCode);
                    if (_loginCallback) _loginCallback((Result)replayCode);
                }
            }
                break;
            case 1:
            {
                if (modId == LOGIN_MOD_ID)
                {
                    net::BasicDecoder d(pkt->buffer());
                    int64_t userId = d.readInt64();
                    uint8_t code = d.readUInt8();
                    int len = d.readUInt16();
                    if (len == 0)
                    {
                        if (_loginCallback) _loginCallback(Result::NO_ROLE_ERROR);
                    }
                    else
                    {
//                        std::string userName = d.readString(len);
                        if (_loginCallback) _loginCallback(Result::SUCCESS);
                    }
                }
                break;
            }
            case 3:
            {
                if (modId == LOGIN_MOD_ID)
                {
                    net::BasicDecoder d(pkt->buffer());
                    app::message::HeroProto hero;
                    d.readMessage(hero);
                    DBG_LOG("create role scuccess---------->%d", hero.level());
                }
                break;
            }
            case 4:
            {
                if (modId == LOGIN_MOD_ID)
                {
                    net::BasicDecoder d(pkt->buffer());
                    int code = d.readUInt8();
                    DBG_LOG("create role fail--------->%d", code);
                }
            }
                break;
            default:
                break;
        }
    }

    void onError(int64_t msgId, int error, net::PacketPtr pkt) override
    {

    }

    void sendLogin(int serverId, const std::string&name, const std::function<void(Result)>& callback)
    {
        GamePacketSendHelper h(int64_t(LOGIN_MOD_ID) << 32 | 2, (int)name.size());
        auto& e = h.getEncoder();
        e.writeUInt16(name.size());
        e.writeString(name);
        _loginCallback = callback;
    }

    void sendCreateRole(RoleJob job, const std::string& name, const ResultCallback& callback)
    {
        GamePacketSendHelper h(int64_t(LOGIN_MOD_ID) << 32 | 3, 1 + (int)name.size());
        auto& e = h.getEncoder();
        e.writeUInt8((int)job);
        e.writeUInt16(name.size());
        e.writeString(name);
        _createRoleCallback = callback;
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

    loadServersManifest(_data->_curManifest);
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

void UserManager::connectServer(int serverId, fy::UserManager::ResultCallback callback)
{
    _data->_serverId = serverId;

    unsigned char* ip = nullptr;
    int port = 0;
    for (auto& srv: _data->_servers)
    {
        if (srv.id == serverId)
        {
            ip = srv.ip;
            port = srv.port;
            break;
        }
    }

    GameApp::getInstance()->loadConfigs([=]{

        GameModule::get<NetManager>()->connect("GAME_SERVER", StringUtils::format("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]), port, [this, callback](bool succ){
            auto gameConn = GameModule::get<NetManager>()->getGameConnection();

            if (!gameConn)
            {
                callback(Result::NETWORK_ERROR);
                return;
            }

            _data->_processor->sendLogin(_data->_serverId, _data->curUser.name, [=](Result r){
                callback(r);
            });

            GameModule::get<NetManager>()->setLostCallback([callback]{
                GameModule::get<NetManager>()->setLostCallback(nullptr);
                callback(Result::NETWORK_ERROR);
            });
        });
    });
}

int indexOfAccount(const std::vector<Account>& accounts, const std::string& username)
{
    for (int i = 0; i < accounts.size(); ++ i)
    {
        if (accounts[i].name == username) return i;
    }
    return -1;
}

void UserManager::createUser(const std::string &name, const std::string &password, const ResultCallback &callback)
{
    bool found = indexOfAccount(_data->_accounts, name) != -1;
    if (found)
    {
        callback(Result::USER_NAME_EXISTS);
    }
    else
    {
        _data->_accounts.push_back(Account(name, password, false));
        callback(Result::SUCCESS);
    }
}

void UserManager::flush()
{
    saveSavedAccounts(_data->_accounts, _data->_savedAccounts);
//    if (_data->curUser)
//    {
//        saveUserData(*_data->curUser);
//    }
}

void UserManager::createRole(const std::string &name, fy::RoleJob job, const ResultCallback &callback)
{
    _data->_processor->sendCreateRole(job, name, callback);
}

void UserManager::setTestUser(const std::string &username)
{
    _data->curUser.name = username;
}

void loadSavedAccounts(std::vector<Account>& _accounts, std::vector<Account>& _savedAccounts)
{
    FileUtils* fu = FileUtils::getInstance();
    std::string dataFile = GameApp::getInstance()->getPersistentDataPath() + "accounts.plist";
    if (fu->isFileExist(dataFile))
    {
        ValueMap data = fu->getValueMapFromFile(dataFile);

        {
            const ValueVector& accounts = data.at("accounts").asValueVector();
            _accounts.clear();
            for (auto& v: accounts)
            {
                const ValueMap& account = v.asValueMap();
                _accounts.push_back(Account(account.at("username").asString(), account.at("password").asString(), false));
            }
        }

        {
            const ValueVector& savedAccounts = data.at("savedAccounts").asValueVector();
            _savedAccounts.clear();
            for (auto& v: savedAccounts)
            {
                const ValueMap& accout = v.asValueMap();
                _savedAccounts.push_back(Account(accout.at("username").asString(), accout.at("password").asString(), accout.at("isAutoLogin").asBool()));
            }
        }
    }
}

void saveSavedAccounts(std::vector<Account>& _accounts, std::vector<Account>& _savedAccounts)
{
    FileUtils* fu = FileUtils::getInstance();
    std::string dataFile = GameApp::getInstance()->getPersistentDataPath() + "accounts.plist";

    ValueMap data;
    ValueVector accounts, savedAccounts;

    for (auto& a: _accounts)
    {
        ValueMap map;
        map["username"] = a.name;
        map["password"] = a.password;
        accounts.push_back(Value(map));
    }

    data["accounts"] = std::move(accounts);

    for (auto& a : _savedAccounts)
    {
        ValueMap map;
        map["username"] = a.name;
        map["password"] = a.password;
        map["iaAutoLogin"] = a.isAutoLogin;
        savedAccounts.push_back(Value(map));
    }

    data["savedAccounts"] = std::move(savedAccounts);
    fu->writeToFile(data, dataFile);
}

bool loadUserData(UserInfo& user)
{
    FileUtils* fu = FileUtils::getInstance();
    std::string dataFile = GameApp::getInstance()->getPersistentDataPath() + StringUtils::format("user-%s.plist", user.name.c_str());

    if (!fu->isFileExist(dataFile)) return false;

    ValueMap data = fu->getValueMapFromFile(dataFile);

    const ValueVector& recents = data.at("recents").asValueVector();
    for (auto& v: recents) user.recentServers.push_back(v.asInt());

    return true;
}

void saveUserData(UserInfo& user)
{
    FileUtils* fu = FileUtils::getInstance();
    std::string dataFile = GameApp::getInstance()->getPersistentDataPath() + StringUtils::format("user-%s.plist", user.name.c_str());
    ValueMap data;
    ValueVector recents;

    for (auto v: user.recentServers) recents.push_back(Value(v));

    data["recents"] = std::move(recents);

    fu->writeToFile(data, dataFile);
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
