/**
 * @file  Player.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_PLAYER_H
#define ECS_PLAYER_H

#include "Role.h"

BEGIN_NS_ECS

class Player : public Role
{
public:
    Player();
    virtual ~Player();

    void init(RoleJob job);

    bool navToNpc(int npcId);
    bool navToGate(int gateId);
    bool navToCollectItem(int collectId);
    bool navToTreasure(int itemId);
    bool navToPos(const Vector3& pos);

    void stopNavigation();

    static ComponentHandle<Player> create(RoleJob job);

public:
    static void setCurrent(const ComponentHandle<Player>& player);
    static const ComponentHandle<Player>& getCurrent();

protected:
    virtual void onAwake() override;
    virtual void onDestroy() override;
    virtual void onStart() override;

private:
    static ComponentHandle<Player> _current;
};

template <>
class component_traits<Player>
{
public:
    typedef Role parent_type;
    static const char* name() { return "Player"; }
    static int flags() { return ComponentFlags::HAS_UPDATE | ComponentFlags::HAS_RECEIVE_MESSAGE; }
    static Component* create() { return new Player(); }
};

END_NS_ECS
#endif /* ECS_PLAYER_H */
