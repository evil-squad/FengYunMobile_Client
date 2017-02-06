/**
 * @file  MapManager.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "MathTypes.h"
#include "GameModule.h"

namespace cocos2d
{
    class Node;
}

BEGIN_NS_FY

class MapData;

class MapHandle
{
public:
    MapHandle(MapData* data) : _data(data) {}
    ~MapHandle() {}

    MapData* get() { return _data; }

    cocos2d::Node* getMapLayer();
    cocos2d::Node* getFrontLayer();

    const Size& getSize() const;
    float getMaxHeight() const;

    void adjust(const Vector2& viewPoint);

    Vector3 toMapPoint(const Vector3& pt) const;

    Vector3 toScenePoint(const Vector3& pt) const;

    float calculteDepth(const Vector3& pt) const;

    operator bool() const
    {
        return _data != nullptr;
    }

private:
    MapData* _data;
};

inline bool operator== (const MapHandle& h, std::nullptr_t)
{
    return h;
}

inline bool operator== (std::nullptr_t, const MapHandle& h)
{
    return !h;
}

inline bool operator!= (const MapHandle& h, std::nullptr_t)
{
    return (bool)h;
}

inline bool operator!= (std::nullptr_t, const MapHandle& h)
{
    return (bool)h;
}

class MapManager : public GameModule
{
public:
    MapManager();
    ~MapManager();

    MapHandle createMap(int sceneId);
    void releaseMap(MapHandle map);

    void registerMap(MapHandle map);
    void unregisterMap(MapHandle map);

    MapHandle getCurrentMap();

    static int gridSize();

    static Vector3 toMapPoint(const Vector3& pos);
    static Vector3 toScenePoint(const Vector3& pos);
    static float calculateDepth(const Vector3& pos);

private:
    struct PrivateData;
    PrivateData* _data;
};

END_NS_FY
#endif /* MAPMANAGER_H */
