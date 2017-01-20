/**
 * @file  Role.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_ROLE_H
#define ECS_ROLE_H

#include "ecsbase.h"
#include "RoleTypes.h"
#include "Component.h"
#include "Event.h"
#include "Transform.h"

BEGIN_NS_ECS

class Role : public Component
{
private:
    FaceDir getFaceDir() const { return _faceDir; }
    void setFaceDir(FaceDir);
private:
    FaceDir _faceDir;
};

template <>
class component_traits<Role>
{
public:
    typedef Component parent_type;
    static const char* name() { return "Role"; }
    static int flags() { return 0; }
    static Component* create() { return nullptr; }
};

END_NS_ECS

#endif /* ECS_ROLE_H */
