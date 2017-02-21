/**
 * @file  GameConfigLoader.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 11/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GameConfigLoader.h"
#include "ConfigReaderPlist.h"
#include "cocos2d.h"

BEGIN_NS_FY

class GameMapConfigFinderImpl : public GameMapConfigFinder
{
public:
    GameMapConfigFinderImpl() {}
    ~GameMapConfigFinderImpl() {}

    std::string find(const std::string& map)
    {
        return "";
    }
};

GameConfigLoader::GameConfigLoader()
{
}

GameConfigLoader::~GameConfigLoader()
{
}

std::unique_ptr<GameMapConfigFinder> GameConfigLoader::createMapFinder()
{
    return std::unique_ptr<GameMapConfigFinder>(new GameMapConfigFinderImpl());
}

static std::unique_ptr<ConfigReader> loadConfigFile(const std::string& path)
{
    if (!cocos2d::FileUtils::getInstance()->isFileExist(path)) return nullptr;

    return std::unique_ptr<ConfigReader>(new ConfigReaderPlist(path.c_str()));
}

std::unique_ptr<ConfigReader> GameConfigLoader::load(const std::string &name)
{
    if (name == "hero")
        return loadConfigFile("heroInfos.plist");
    return nullptr;
}

END_NS_FY
