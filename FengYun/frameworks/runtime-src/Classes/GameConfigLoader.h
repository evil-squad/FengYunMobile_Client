/**
 * @file  GameConfigLoader.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 11/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GAMECONFIGLOADER_H
#define GAMECONFIGLOADER_H

#include "gamebase.h"
#include "ConfigReader.h"
#include <string>
#include <memory>

BEGIN_NS_FY

class GameMapConfigFinder
{
public:
    virtual ~GameMapConfigFinder() {}

    virtual std::string find(const std::string& map) = 0;
};

class GameConfigLoader
{
public:
    GameConfigLoader();
    ~GameConfigLoader();

    std::unique_ptr<GameMapConfigFinder> createMapFinder();
    std::unique_ptr<ConfigReader> load(const std::string& name);
};

END_NS_FY
#endif /* GAMECONFIGLOADER_H */
