/**
 * @file  SceneProjector.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 20/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef SCENEPROJECTOR_H
#define SCENEPROJECTOR_H

namespace fy
{
    class SceneProjector
    {
    public:
        static Vector3 project(const Vector3& pos)
        {
            return Vector3(pos.x, pos.y, pos.z);
        }

        static Vector3 inverseProject(const Vector3& pos)
        {
            return Vector3(pos.x, pos.y, pos.z);
        }
    };
}


#endif /* SCENEPROJECTOR_H */
