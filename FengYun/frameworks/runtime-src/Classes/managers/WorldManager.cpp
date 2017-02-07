/**
 * @file  WorldManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "WorldManager.h"
#include "GameConfigLoader.h"
#include "AStar.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

BEGIN_NS_FY

///////////////////TODO: class PrivateData
struct WorldManager::PrivateData
{
    class PathCalculator;
    std::vector<int> searchPath;
    AStar astar;

    PrivateData()
    {}

    ~PrivateData()
    {}
};

//////////////////////TODO: class PathCalculator
class WorldManager::PrivateData::PathCalculator : public AStar::Calculator
{
public:
    PathCalculator(PrivateData& data) : _data(data) {}
    virtual ~PathCalculator() {}

    virtual const std::vector<std::pair<int, int> >& getLinks(int id) override
    {
        links.clear();


        return links;
    }

    virtual int calculateH(int id, int end) override
    {
        return 100;
    }

private:
    std::vector<std::pair<int, int> > links;
    PrivateData& _data;
};

////////////////////TODO: class WorldManager
WorldManager::WorldManager()
{
    _data = new PrivateData();
}

WorldManager::~WorldManager()
{
    delete _data;
}

const std::vector<int>& WorldManager::searchPath(int aMap, int bMap)
{
    PrivateData::PathCalculator calc(*_data);

    _data->searchPath.clear();
    if (_data->astar.searchPath(-aMap, -bMap, _data->searchPath, calc))
    {
        int c = ((int)_data->searchPath.size() + 1) / 2;
        for (int i = 0; i < c; ++i) _data->searchPath[i * 2] = _data->searchPath[i * 2];
        return _data->searchPath;
    }

    return _data->searchPath;
}

void WorldManager::onInitialize()
{

}

void WorldManager::onRelease()
{

}

void WorldManager::onLoadConfig(fy::GameConfigLoader *loader)
{

}

END_NS_FY
