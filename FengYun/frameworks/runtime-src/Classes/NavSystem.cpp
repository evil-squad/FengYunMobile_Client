/**
 * @file  NavSystem.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "NavSystem.h"
#include "DebugHelper.h"

USING_NS_CC;
using namespace std;

namespace fy
{
    class MapPathCalculator : public AStar::Calculator
    {
    public:
        MapPathCalculator(int w, int h, const BitArray& bits) : _width(w), _height(h), _bits(bits) {}
        virtual ~MapPathCalculator() {}

        virtual const std::vector<std::pair<int, int> >& getLinks(int id) override
        {
            _links.clear();

            int x, y;
            getXY(id, x, y);

            int nid, xx, yy, i, j;
            for (i=0; i<3; ++i)
                for (j=0; j<3; ++j)
                {
                    if (i == 1 && j == 1) continue;

                    xx = x + i - 1;
                    yy = y + j - 1;
                    nid = getId(xx, yy);

                    if (i == 1 || j == 1)
                    {
                        if (isPassable(xx, yy))
                            _links.push_back(make_pair(nid, 10));
                    }
                    /* FIXME: check whether blocked by non-walkable block */
                    else
                    {
                        if (isPassable(xx, yy))
                            _links.push_back(make_pair(nid, 14));
                    }
                }

            return _links;
        }

        virtual int calculateH(int id, int end) override
        {
            int x1, x2, y1, y2;
            getXY(id, x1, y1);
            getXY(end, x2, y2);

            int x = x1 > x2 ? x1 - x2 : x2 - x1;
            int y = y1 > y2 ? y1 - y2 : y2 - y1;
            return (x + y) * 10;
        }

        inline int getId(int x, int y)
        {
            return y * _width + x + 1;
        }

        inline void getXY(int id, int& x, int& y)
        {
            x = (id - 1) % _width;
            y = (id - 1 - x) / _width;
        }

    private:
        int _width, _height;
        const BitArray& _bits;
        std::vector<std::pair<int, int> > _links;

        inline bool isPassable(int x, int y)
        {
            if (x < 0 || y < 0 || x >= _width || y >= _height) return false;
            return _bits.at(y * _width + x);
        }
    };

    NavSystem* NavSystem::getInstance()
    {
        static NavSystem* _instance = nullptr;
        if (!_instance)
            _instance = new NavSystem();
        return _instance;
    }

    NavSystem::NavSystem() : _width(0), _height(0)
    {
    }

    NavSystem::~NavSystem()
    {
    }

    static unsigned int readUInt16(const unsigned char* buf, int& idx)
    {
        const unsigned char* ptr = buf + idx;
        idx += 2;
        return ptr[0] << 8 | ptr[1];
    }

    static unsigned int readUInt32(const unsigned char* buf, int& idx)
    {
        const unsigned char* ptr = buf + idx;
        idx += 4;
        return ptr[0] << 24 | ptr[1] << 16 | ptr[2] << 8 | ptr[3];
    }

    bool NavSystem::load(const unsigned char* buf, size_t size)
    {
        int idx = 0;
        unsigned int w = readUInt16(buf, idx);
        unsigned int h = readUInt16(buf, idx);
        unsigned int count = readUInt16(buf, idx);

        _width = w;
        _height = h;

        _barr.reserve(w*h);

        _barr.reset(true);
        for (int i=0; i<count; ++i)
        {
            unsigned int id = readUInt32(buf, idx);
            int x = (id >> 16) & 0xffff;
            int y = id & 0xffff;
            DBG_ASSERT(x < w && y < h, "map data error!");
            _barr.set(y*w + x, false);
        }
        return true;
    }

    // need inline it to calculatePath, strip path in-place
    static inline void stripPath(std::vector<Vector3>& path)
    {
        std::vector<Vector3> tmp;
        tmp.swap(path);

        Vector3* cur = &tmp[0];
        Vector3* prev;
        Vector3* end = &tmp[tmp.size()-1] + 1;

        prev = cur;
        cur++;

        Vector3 dir;
        Vector3 lastDir = Vector3::ZERO;
        while (cur != end)
        {
            dir = *cur - *prev;
            if (dir != lastDir)
            {
                path.push_back(*prev);
                lastDir = dir;
            }

            prev = cur;
            cur++;
        }

        path.push_back(tmp[tmp.size()-1]);
    }

    NavPath* NavSystem::calculatePath(const Vector3& a, const Vector3& b)
    {
        MapPathCalculator calc(_width, _height, _barr);
        int ax = (int)a.x;
        int ay = (int)a.y;
        int bx = (int)b.x;
        int by = (int)b.y;

        std::vector<int> path;
        if (_astar.searchPath(calc.getId(ax, ay), calc.getId(bx, by), path, calc))
        {
            int x, y;
            NavPath* p = new NavPath();
            for (auto node: path)
            {
                calc.getXY(node, x, y);
                p->path.push_back(Vector3(x, y, 0));
            }
            stripPath(p->path);
            return p;
        }

        return nullptr;
    }

    void NavSystem::releasePath(NavPath* path)
    {
        delete path;
    }

    bool NavSystem::isGround(const Vector3& pt)
    {
        if (pt.z == 0) return true;
        return false;
    }
    
    bool NavSystem::isWalkable(const Vector3& pt)
    {
        if  (pt.z > 0) return false;
        
        int x = (int)pt.x;
        int y = (int)pt.y;
        
        if (x < 0 || x >= _width ||
            y < 0 || y >= _height) return false;
        
        return _barr.at(y*_width + x);
    }
    
    void NavSystem::setMapDataAtPoint(const Vector3& pt, int width, int height, bool isWalkable)
    {
        if (pt.z > 0) return;
        
        int x = (int)pt.x;
        int y = (int)pt.y;
        
        int minX = x - width;
        int maxX = x + width;
        int minY = y - height;
        int maxY = y + height;
        
        minX = MAX(0, minX);
        maxX = MIN(maxX, _width - 1);
        minY = MAX(0, minY);
        maxY = MIN(maxY, _height - 1);
        
        for (int i = minX; i <= maxX; i ++)
        {
            for (int j = minY; j <= maxY; j ++)
            {
                _barr.set(j*_width + i, isWalkable);
            }
        }
    }
    
    Vector3 NavSystem::findGround(const Vector3& pt)
    {
        return Vector3(pt.x, pt.y, 0);
    }
}

