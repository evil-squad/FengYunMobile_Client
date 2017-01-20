/**
 * @file  Transform.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef ECS_TRANSFORM_H
#define ECS_TRANSFORM_H

#include "ecsbase.h"
#include "Component.h"
#include "MathTypes.h"
#include <set>
#include <vector>

BEGIN_NS_ECS

class Transform : public Component
{
public:
    typedef std::set<ComponentHandle<Transform> >::const_iterator const_iterator;

public:
    Transform();

    const ComponentHandle<Transform>& getParent() const { return _parent; }
    void setParent(const ComponentHandle<Transform>& parent);

    const Vector3& getPosition() const { return _position; }
    void setPosition(const Vector3& position);

    Vector3 getWorldPosition() const;
    std::size_t getChildCount() const { return _children.size(); }

    const_iterator begin() const { return _children.cbegin(); }
    const_iterator end() const { return _children.cend(); }

protected:
    virtual void onDestroy() override;

private:
    ComponentHandle<Transform> _parent;
    std::set<ComponentHandle<Transform> > _children;
    Vector3 _position;
};

template<>
struct component_traits<Transform>
{
    typedef Component parent_type;
    static const char* name() { return "Transform"; }
    static int flags() { return 0; }
    static Component* create() { return new Transform(); }
};

class TransformChangeEvent : public Event<TransformChangeEvent>
{
public:
    static const char* getTypeName() { return "TransformChangeEvent"; }

    TransformChangeEvent(const ComponentHandle<Transform>& t)
    : transform(t)
    {}

    ComponentHandle<Transform> transform;
};

END_NS_ECS
#endif /* ECS_TRANSFORM_H */
