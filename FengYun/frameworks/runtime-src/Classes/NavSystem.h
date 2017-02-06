/**
 * @file  NavSystem.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef NAVSYSTEM_H
#define NAVSYSTEM_H

#include "MathTypes.h"
#include "BitArray.h"
#include "AStar.h"

namespace fy
{
    class NavPath
    {
    public:
        std::vector<Vector3> path;
    };

    // notice: nav system only accept map coordinate
    class NavSystem
    {
    public:
        static NavSystem* getInstance();

        bool load(const unsigned char* buf, size_t size);

        NavPath* calculatePath(const Vector3& a, const Vector3& b);
        void releasePath(NavPath* path);

        bool isGround(const Vector3& pt);
        bool isWalkable(const Vector3& pt);

        void setMapDataAtPoint(const Vector3& pt, int width, int height, bool isWalkable);

        Vector3 findGround(const Vector3& pt);

    private:
        NavSystem();
        ~NavSystem();
        
        int _width, _height;
        AStar _astar;
        BitArray _barr;
    };
}

#endif /* NAVSYSTEM_H */
