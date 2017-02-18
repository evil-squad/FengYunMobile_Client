/**
 * @file  UserManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/14.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "gamebase.h"
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>

#include "RoleData.h"
#include "GameModule.h"

BEGIN_NS_FY

struct UserInfo
{
    UserInfo() {}
    std::string name;
    std::vector<int> recentServers;
};


class UserManager : public GameModule
{
public:
    enum class Result
    {
        SUCCESS = 0,
        NO_USER_ERROR,
        USER_NAME_EXISTS,
        WRONG_USER_PASSWORD,
        USER_PROHIBIT,
        NO_ROLE_ERROR,
        ROLE_NAME_EXISTS,
        NETWORK_ERROR,
        UNKNOWN_ERROR,
        VERSION_DEBUG_ERROR,
        VERSION_PROTOCAL_ERROR,
        VERSION_PROTOCAL_WRONG,
        VERSION_RESOUCE_WRONG
    };

    struct ServerEntry
    {
        int id;
        std::string name;
        int busy;
        unsigned char ip[4];
        int port;

        ServerEntry(int id_, const std::string& name_, int busy_, unsigned char ip_[4], int port_)
        {
            id = id_;
            name = name_;
            busy = busy_;
            for (int i = 0; i < 4; ++i) ip[i] = ip_[i];
            port = port_;
        }
    };

    struct LoginOptions
    {
        bool isSave;
        bool isAutoLogin;
    };

    typedef std::function<void(Result)> ResultCallback;

    UserManager();
    ~UserManager();

    void onLoadConfig(GameConfigLoader* loader) override;
    void onInitialize() override;
    void onRelease() override;

    void updateServers(const ResultCallback& callback);

    const std::vector<ServerEntry>& getServers();

    void connectServer(int serverId, ResultCallback callback);

    void createUser(const std::string& name, const std::string& password, const ResultCallback& callback);
    void createRole(const std::string& name, RoleJob job, const ResultCallback& callback);

    void setTestUser(const std::string& username);

    void flush();

    std::string getAccountType();

    struct PrivateData;
private:
    class Listener;
    class Processor;

    PrivateData* _data;
};

END_NS_FY
#endif /* USERMANAGER_H */
