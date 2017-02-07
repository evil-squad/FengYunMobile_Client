/**
 * @file  NavAgent.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/7.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_NAVAGENT_H
#define ECS_NAVAGENT_H

#include "ecsbase.h"
#include "Component.h"
#include "MathTypes.h"

BEGIN_NS_ECS

class NavAgent : public Component
{
public:
    NavAgent();
    virtual ~NavAgent();

    float getSpeed() const { return _speed; }
    void setSpeed(float speed) { _speed = speed; }

    const Vector3& getVelocity() const { return _velocity; }

    void setDestination(const Vector3& position);
    void stop();

    bool isNavigating() const { return _navigating; }

    void setIsThrough(bool through) { _isThrough = through; }
    bool isThrough() const { return _isThrough; }

    void resetPosition();

    const Vector3& getNextPoint() const;

protected:
    virtual void onStart() override;
    virtual void onUpdate(float dt) override;

private:
    bool _navigating;
    bool _isThrough;
    float _speed;
    Vector3 _lastPos;
    Vector3 _velocity;
    std::queue<Vector3> _path;
};

template<>
struct component_traits<NavAgent>
{
    typedef Component parent_type;
    static const char* name() { return "NavAgent"; }
    static int flags() { return ComponentFlags::HAS_UPDATE; }
    static Component* create() { return new NavAgent(); }
};

END_NS_ECS
#endif /* ECS_NAVAGENT_H */
