/**
 * @file  Component.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 17/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Component.h"
#include "Entity.h"

BEGIN_NS_ECS

void Component::setEnabled(bool value)
{
    if (_enabled == value) return;

    _enabled = value;
    if (!_entity->isActiveInHierarchy() || !_entity->getWorld()->isRunning())
        return;

    if (value)
        _entity->getWorld()->addComponentEnableCommand(_id);
    else
        _entity->getWorld()->addComponentDisableCommand(_id);
}

World* Component::getWorld() const
{
    return getEntity()->getWorld();
}

void* Component::getWorldUserData() const
{
    return getWorld()->getUserData<void>();
}

END_NS_ECS
