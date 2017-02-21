/**
 * @file  MapManager.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "MapManager.h"
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <set>

#include "GameConfigLoader.h"
#include "SceneProjector.h"
#include "NavSystem.h"

#include "GameApp.h"
#include "DebugHelper.h"

#include "json/document.h"

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
        , _mapTileWidth(0)
        , _tileName("")
        , _tilePath("")
        , _maxHerTileCount(0)
        , _maxVerTileCount(0)
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

    void adjust(const Vector2& pt);

    const Size& getSize() const { return _size; }
    void setSize(const Size& size) { _size = size; }

    float getMaxHeight() const { return _maxHeight; }
    void setMaxHeight(float h) { _maxHeight = h; }

    const Data& getNavData() const { return _navData; }
    void setNavData(Data data) { _navData = std::move(data); }

    void setMapTileWidth(int width) { _mapTileWidth = width; }
    int getMapTileWidth() const { return _mapTileWidth; }

    void setTileName(const std::string& name) { _tileName = name; }
    const std::string& getTileName() const { return _tileName; }

    void setTilePath(const std::string& path) { _tilePath = path; }
    const std::string& getTilePath() const { return _tilePath; }

    void calculateTileCount()
    {
        _maxHerTileCount = std::ceil(_size.width / _mapTileWidth);
        _maxVerTileCount = std::ceil(_size.width / _mapTileWidth);

        const auto& size = Director::getInstance()->getVisibleSize();
        xTileCount = std::ceil(size.width / _mapTileWidth) + 1;
        yTileCount = std::ceil(size.height / _mapTileWidth) + 1;
    }

private:
    cocos2d::Node* _mapLayer;
    cocos2d::Node* _frontLayer;
    Size _size;
    float _maxHeight;
    Data _navData;
    int _mapTileWidth;
    std::string _tileName;
    std::string _tilePath;

    unordered_map<std::string, Sprite*> curTiles;
    set<std::string> curKeys;
    set<std::string> newKeys;

    //max count of tiles for cur map
    int _maxHerTileCount;
    int _maxVerTileCount;

    //count of tiles for screen view
    int xTileCount;
    int yTileCount;
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

    _mapLayer->addChild(node, 1);
}

inline void MapData::adjust(const Vector2 &pt)
{
    int xStartIdx = std::floor(pt.x / _mapTileWidth);
    int yStartIdx = std::floor(pt.y / _mapTileWidth);
    newKeys.clear();
    for (int x = 0; x < xTileCount; ++ x)
    {
        for ( int y = 0; y < yTileCount; ++ y)
        {
            int xIdx = xStartIdx + x;
            int yIdx = yStartIdx + y;

            if (xIdx >= _maxHerTileCount || yIdx >= _maxVerTileCount || xIdx < 0 || yIdx < 0)
                continue;

            char name[128] = {0};
            sprintf(name, "%s/%s%d_%d.jpg", _tilePath.c_str(), _tileName.c_str(), xIdx, yIdx);
            string key = string(name);
            newKeys.insert(key);
        }
    }

    set<string> results;
    set_difference(curKeys.begin(), curKeys.end(), newKeys.begin(), newKeys.end(), inserter(results, results.begin()));
    for (auto it = results.begin(); it != results.end(); ++ it)
    {
        curTiles[*it]->removeFromParent();
        curTiles.erase(*it);
    }

    results.clear();
    set_difference(newKeys.begin(), newKeys.end(), curKeys.begin(), curKeys.end(), inserter(results, results.begin()));
    for (auto it = results.begin(); it != results.end(); ++ it)
    {
        Sprite* tile = Sprite::create(*it);
        DBG_LOG("map file name:%s", (*it).c_str());
        tile->setIgnoreAnchorPointForPosition(true);
        int xIdx = 0;
        int yIdx = 0;
//        char path[128] = {0};
//        sprintf(path, "%s/%s", _tilePath.c_str(), _tileName.c_str());

        sscanf((*it).c_str(), "maps/guide/guide%d_%d.jpg",  &xIdx, &yIdx);
        int posX = _mapTileWidth * xIdx;
        int posY = _mapTileWidth * yIdx;
        tile->setPosition(Vec2(posX, posY));
        _mapLayer->addChild(tile);

//        DebugHelper::debugDraw(tile);

        curTiles[*it] = tile;
    }

    curKeys = newKeys;
    newKeys.clear();
//    Director::getInstance()->getTextureCache()->removeUnusedTextures();
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

void MapHandle::adjust(const Vector2 &viewPoint)
{
    _data->adjust(viewPoint);
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
//    map.get()->debugMap();
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

inline static std::string getDirname(const std::string& path)
{
    std::size_t lastIndex = path.find_last_of("/");
    return path.substr(0, lastIndex);
}

static MapData* createMapData(int sceneId)
{
    std::string path = "maps/guide/guide.json";
    string str = cocos2d::FileUtils::getInstance()->getStringFromFile(path);

    std::string dirname = getDirname(path);

    rapidjson::Document doc;
    doc.Parse<0>(str.c_str());
    if (doc.HasParseError())
    {
        DBG_LOG("Map Error '%u' on parse '%s'", doc.GetParseError(), str.c_str());
        return nullptr;
    }

    MapData* data = new MapData();

    Size size;
    size.width = doc["width"].GetInt();
    size.height = doc["height"].GetInt();
    data->setSize(size);
    data->setMaxHeight(doc["maxHeight"].GetInt());
    data->setTileName(doc["tileName"].GetString());
    data->setMapTileWidth(doc["mapTileWidth"].GetInt());
    data->setTilePath(dirname);
    data->calculateTileCount();

    std::string mapFilePath = doc["mapFile"].GetString();
    if (!dirname.empty()) mapFilePath = dirname + "/" + mapFilePath;
    Data mapData = FileUtils::getInstance()->getDataFromFile(mapFilePath);
    data->setNavData(std::move(mapData));

    cocos2d::Node* node = Node::create();
    node->setContentSize(size);
    data->setMapLayer(node);

    return data;
}


END_NS_FY
