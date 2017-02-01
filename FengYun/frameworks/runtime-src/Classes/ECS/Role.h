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
#include "Avatar.h"

namespace fy
{
    namespace fsm
    {
        class Fsm;
        class BaseData;
    }

    namespace net
    {
        class AgentMsg;
    }

    namespace scenes
    {
        class GameScene;
    }
}

BEGIN_NS_ECS

class SceneAgentEvent : public Event<SceneAgentEvent>
{
public:
    static const char* getTypeName() { return "SceneAgentEvent"; }

    SceneAgentEvent(const net::AgentMsg& msg_)
        : msg(msg_)
    {}

    const net::AgentMsg& msg;
};

class Role : public Component
{
public:
    RoleType getRoleType() const { return _roleType; }
    void setRoleType(RoleType type) { _roleType = type; }

    FaceDir getFaceDir() const { return _faceDir; }
    void setFaceDir(FaceDir dir);

    const ComponentHandle<Transform>& getTransform();
    const std::string& getName() const { return _name; }

    const ComponentHandle<Avatar>& getAvatar() { return _avatar; }
    scenes::GameScene* getScene() { return getWorldUserData<scenes::GameScene>(); }
protected:
    Role(const ComponentType<Component>& type, RoleType roleType);
    virtual ~Role();
    bool init(const std::string& name, bool hasFsm);

    virtual void onUpdate(float dt) override;
    virtual void onReceive(const Event<void>& ev) override;

    virtual void onStart() override;
    virtual void onDestroy() override;

    fsm::Fsm* _fsm;
    fsm::BaseData* _fsmData;
    ComponentHandle<Avatar> _avatar;

private:
    FaceDir _faceDir;
    RoleType _roleType;
    std::string _name;
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
