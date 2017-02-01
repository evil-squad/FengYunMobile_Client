/**
 * @file  Renderer.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "Renderer.h"
#include "cocos2d.h"

BEGIN_NS_ECS

Renderer::Renderer()
    : Component(component_type<Renderer>())
{
    _displayNode = cocos2d::Node::create();
    _displayNode->setVisible(false);
    _displayNode->retain();
}

Renderer::~Renderer()
{
    _displayNode->release();
}

void Renderer::onEnable()
{
    _displayNode->setVisible(true);
}

void Renderer::onDisable()
{
    _displayNode->setVisible(false);
}

END_NS_ECS
