/**
 * @file  AStar.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ASTAR_H
#define ASTAR_H

#include <vector>

struct AStarData_t;

class AStar
{
public:
    class Calculator
    {
    public:
        virtual ~Calculator() {}

        virtual const std::vector<std::pair<int, int> >& getLinks(int id) = 0;
        virtual int calculateH(int id, int end) = 0;
    };

    AStar();
    ~AStar();

    bool searchPath(int start, int end, std::vector<int>& path, Calculator& calc);

private:
    struct AStarData_t* _data;
};

#endif /* ASTAR_H */
