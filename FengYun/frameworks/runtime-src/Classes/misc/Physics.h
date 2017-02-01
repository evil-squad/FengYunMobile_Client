/**
 * @file  Physics.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef PHYSICS_H
#define PHYSICS_H

namespace fy
{
    class Physics
    {
    public:

        static float gravity() { return _gravity; }
        static void setGravity(float gravity) { _gravity = gravity; }

    private:
        Physics();
        ~Physics();

        static float _gravity;

        static Physics* getInstance();
    };
}

#endif /* PHYSICS_H */
