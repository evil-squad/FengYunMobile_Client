/**
 * @file  LocalBattleController.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "LocalBattleController.h"

BEGIN_NS_SCENES

LocalBattleController::LocalBattleController(GameScene* scene)
    : _scene(scene)
{
}

LocalBattleController::~LocalBattleController()
{
}

void LocalBattleController::setPlayer(RoleHandle role)
{

}

void LocalBattleController::onStanding(RoleHandle role)
{

}

void LocalBattleController::onMove(RoleHandle role, bool isRunnint, const Vector3 &step)
{

}

void LocalBattleController::onStopMove(RoleHandle role)
{

}

void LocalBattleController::onJump(RoleHandle role, const Vector2 &speed)
{

}

void LocalBattleController::onCastSkill(RoleHandle role, int skillId)
{

}

void LocalBattleController::onCastSkillSegment(RoleHandle role, int skillId, int segId, int repeatCount)
{

}

void LocalBattleController::onBeginSkill(RoleHandle role)
{

}

void LocalBattleController::onEndSkill(RoleHandle role)
{

}

void LocalBattleController::onBreakSkill(RoleHandle role, RoleHandle interrupter)
{

}

void LocalBattleController::onEmit(RoleHandle role, int emitId, float delay)
{

}

void LocalBattleController::update(float dt)
{

}

void LocalBattleController::onSceneQuit()
{

}

void LocalBattleController::onBattleComplete()
{

}

void LocalBattleController::onHandleMessage(const fy::scenes::BattleMessage &msg)
{

}

void LocalBattleController::onSceneEnter()
{

}

void LocalBattleController::onSceneExit()
{
    
}

END_NS_SCENES
