/**
 * @file  MapManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "MapManager.h"
#include <memory>

#include "GameConfigLoader.h"
#include "SceneProjector.h"
#include "NavSystem.h"

#include "GameApp.h"
#include "DebugHelper.h"

#define MAP_TILE_SIZE 32

USING_NS_CC;

using namespace std;

BEGIN_NS_FY

class MapData
{
public:
    MapData()
        : _mapLayer(nullptr)
        , _frontLayer(nullptr)
    {}

    ~MapData()
    {
        if (_mapLayer)
            _mapLayer->release();
        if (_frontLayer)
            _frontLayer->release();
    }

    cocos2d::Node* getMapLayer() const { return _mapLayer; }
    cocos2d::Node* getFrontLayer() const { return _frontLayer; }

    void setMapLayer(cocos2d::Node* layer)
    {
        DBG_ASSERT(_mapLayer == nullptr, "Map layer already exists!");
        layer->retain();
        _mapLayer = layer;
    }

    void setFrontLayer(cocos2d::Node* layer)
    {
        DBG_ASSERT(_frontLayer == nullptr, "Front layer already exists!");
        layer->retain();
        _frontLayer = layer;
    }

    void debugMap();

    const Size& getSize() const { return _size; }
    void setSize(const Size& size) { _size = size; }

    float getMaxHeight() const { return _maxHeight; }
    void setMaxHeight(float h) { _maxHeight = h; }

    const Data& getNavData() const { return _navData; }
    void setNavData(Data data) { _navData = std::move(data); }

private:
    cocos2d::Node* _mapLayer;
    cocos2d::Node* _frontLayer;
    Size _size;
    float _maxHeight;
    Data _navData;
};

static inline void addMapPointRect(DrawNode* node, MapHandle map, int x, int y, const Color4F& color)
{
    auto pos = map.toScenePoint(Vector3(x, y, 0));
    float w = MAP_TILE_SIZE;
    float h = MAP_TILE_SIZE;

    Vec2 vertices[] =
    {
        Vec2(pos.x - w/2, pos.y + h/2),
        Vec2(pos.x + w/2, pos.y + h/2),
        Vec2(pos.x + w/2, pos.y - h/2),
        Vec2(pos.x - w/2, pos.y - h/2)
    };

    node->drawPolygon(vertices, 4, color, 1, Color4F(0.2f, 0.2f, 0.2f, 1));
}

inline void MapData::debugMap()
{
    int w = (int)(_size.width / MAP_TILE_SIZE);
    int h = (int)(_size.height / MAP_TILE_SIZE);

    auto node = DrawNode::create();
    auto nav = NavSystem::getInstance();

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            if (!nav->isWalkable(Vector3(x, y, 0)))
            {
                addMapPointRect(node, MapHandle(this), x, y, Color4F(1, 0, 0, 0.2));
            }
            else
            {
                addMapPointRect(node, MapHandle(this), x, y, Color4F(0, 1, 0, 0.2));
            }
        }
    }

    _mapLayer->addChild(node);
}

Node* MapHandle::getMapLayer()
{
    return _data->getMapLayer();
}

Node* MapHandle::getFrontLayer()
{
    return _data->getFrontLayer();
}

const Size& MapHandle::getSize() const
{
    return _data->getSize();
}

float MapHandle::getMaxHeight() const
{
    return _data->getMaxHeight();
}

Vector3 MapHandle::toMapPoint(const Vector3 &pt) const
{
    auto& mapSize = _data->getSize();
    Vector3 p = SceneProjector::project(pt);
    int x = (int)(p.x / MAP_TILE_SIZE);
    x = p.x < 0 ? (x - 1) : x;
    float y = (mapSize.height - 1 - p.y) / MAP_TILE_SIZE;
    return Vector3(x, (int)y, (int)(p.z / MAP_TILE_SIZE));
}

Vector3 MapHandle::toScenePoint(const Vector3 &pt) const
{
    auto& mapSize = _data->getSize();
    float y = mapSize.height - pt.y * MAP_TILE_SIZE - MAP_TILE_SIZE / 2;
    Vector3 p(pt.x * MAP_TILE_SIZE + MAP_TILE_SIZE / 2, y, pt.z * MAP_TILE_SIZE);
    return SceneProjector::inverseProject(p);
}

float MapHandle::calculteDepth(const Vector3 &pt) const
{
    auto& mapSize = _data->getSize();
    Vector3 p = SceneProjector::project(pt);
    return clampf(p.y / mapSize.height, 0, 1);
}

/////////////////TODO: MapManager PrivateData class
struct MapManager::PrivateData
{
    MapHandle map;

    PrivateData()
        : map(nullptr)
    {
    }

    ~PrivateData()
    {}
};

MapManager::MapManager()
{
    _data = new PrivateData();
}

MapManager::~MapManager()
{
    delete _data;
}

static MapData* createMapData(int sceneId);

MapHandle MapManager::createMap(int sceneId)
{
    return MapHandle(createMapData(sceneId));
}

void MapManager::releaseMap(fy::MapHandle map)
{
    delete map.get();
}

void MapManager::registerMap(fy::MapHandle map)
{
    DBG_ASSERT(map.get() != nullptr, "Invalid map!");
    DBG_ASSERT(_data->map.get() == nullptr, "Already has map!");
    _data->map = map;
    auto& navData = map.get()->getNavData();
    NavSystem::getInstance()->load(navData.getBytes(), navData.getSize());
    map.get()->debugMap();
}

void MapManager::unregisterMap(fy::MapHandle map)
{
    DBG_ASSERT(_data->map.get() == map.get(), "Map not match!");
    _data->map = MapHandle(nullptr);
}

MapHandle MapManager::getCurrentMap()
{
    return _data->map;
}

int MapManager::gridSize()
{
    return MAP_TILE_SIZE;
}

Vector3 MapManager::toMapPoint(const Vector3 &pos)
{
    auto mgr = GameModule::get<MapManager>();
    if (mgr->_data->map)
    {
        MapHandle map(mgr->_data->map);
        return map.toMapPoint(pos);
    }
    return Vector3::ZERO;
}

Vector3 MapManager::toScenePoint(const Vector3 &pos)
{
    auto mgr = GameModule::get<MapManager>();
    if (mgr->_data->map)
    {
        MapHandle map(mgr->_data->map);
        return map.toScenePoint(pos);
    }
    return Vector3::ZERO;
}

float MapManager::calculateDepth(const Vector3 &pos)
{
    auto mgr = GameModule::get<MapManager>();
    if (mgr->_data->map)
    {
        MapHandle map(mgr->_data->map);
        return map.calculteDepth(pos);
    }
    return 0;
}

static MapData* createMapData(int sceneId)
{
    MapData* data = new MapData();

    return data;
}


END_NS_FY
