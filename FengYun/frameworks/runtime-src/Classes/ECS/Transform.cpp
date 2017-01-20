/**
 * @file  Transform.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Transform.h"
#include "Entity.h"
#include "World.h"

BEGIN_NS_ECS

Transform::Transform()
: Component(component_type<Transform>())
{}

void Transform::onDestroy()
{
    if (_parent)
    {
        _parent->_children.erase(ComponentHandle<Transform>(this));
    }
    else
    {
        getEntity()->getWorld()->removeRootEntity(__handle_internal::id(getEntity()));
    }
}

void Transform::setParent(const ComponentHandle<fy::ecs::Transform> &parent)
{
    if (_parent != parent)
    {
        ComponentHandle<Transform> h(this);
        if (_parent)
            _parent->_children.erase(h);
        if (parent)
            parent->_children.insert(h);

        auto old = _parent;
        _parent = parent;

        if (old)
        {
            getEntity()->getWorld()->addRootEntity(__handle_internal::id(getEntity()));
        }
        else
            getEntity()->getWorld()->removeRootEntity(__handle_internal::id(getEntity()));

        __entity_internal::on_parent_change(getEntity().get(), old, parent);

        getWorld()->emitEvent(TransformChangeEvent(ComponentHandle<Transform>(this)));
    }
}

void Transform::setPosition(const Vector3 &position)
{
    if (_position != position)
    {
        _position = position;
        getWorld()->emitEvent(TransformChangeEvent(ComponentHandle<Transform>(this)));
    }
}

Vector3 Transform::getWorldPosition() const
{
    return _parent ? _parent->getWorldPosition() + _position : _position;
}

END_NS_ECS
