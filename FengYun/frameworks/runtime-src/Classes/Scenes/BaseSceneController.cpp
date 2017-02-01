/**
 * @file  BaseSceneController.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/30.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "BaseSceneController.h"
#include "ECS/Player.h"
#include "ECS/Entity.h"
#include "ECS/Agent.h"

USING_NS_ECS;
BEGIN_NS_SCENES

BaseSceneController::BaseSceneController(GameScene* scene)
    : _scene(scene)
{}

BaseSceneController::~BaseSceneController()
{}

void BaseSceneController::onSetPlayerAgent(int id, const Vector3 &pt, fy::FaceDir face, const std::function<void ()> &cb)
{
    auto player = Player::create(fy::RoleJob::BUJINGYUN);
    Player::setCurrent(player);
    auto pos = Vector2(pt.x, pt.y);

    player->getTransform()->setPosition(pt);
    player->setFaceDir(face);

    auto agent = player->getEntity()->addComponent<Agent>();
    agent->setAgentId(id);

}

END_NS_SCENES
