/**
 * @file  LocalBattleController.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef LOCALBATTLECONTROLLER_H
#define LOCALBATTLECONTROLLER_H

#include "scenebase.h"
#include "GameScene.h"
#include "BattleController.h"

namespace std
{
    template<>
    struct hash<std::pair<int, int> >
    {
        std::size_t operator()(const std::pair<int, int>& v) const
        {
            auto h1 = std::hash<int>()(v.first);
            auto h2 = std::hash<int>()(v.second);
            return h1 ^ (h2 << 1);
        }
    };
}

BEGIN_NS_SCENES

class LocalBattleController : public BattleController
{
public:
    LocalBattleController(GameScene* scene);
    virtual ~LocalBattleController();

    void setPlayer(RoleHandle role) override;

    void onStanding(RoleHandle role) override;

    void onMove(RoleHandle role, bool isRunnint, const Vector3& step) override;
    void onStopMove(RoleHandle role) override;
    void onJump(RoleHandle role, const Vector2& speed) override;

    void onCastSkill(RoleHandle role, int skillId) override;
    void onCastSkillSegment(RoleHandle role, int skillId, int segId, int repeatCount) override;

    void onBeginSkill(RoleHandle role) override;
    void onEndSkill(RoleHandle role) override;
    void onBreakSkill(RoleHandle role, RoleHandle interrupter) override;

    void onEmit(RoleHandle role, int emitId, float delay = 0) override;

    void update(float dt) override;

    void onSceneQuit() override;
    void onBattleComplete() override;

    void onHandleMessage(const BattleMessage& msg) override;

    void onSceneEnter() override;
    void onSceneExit() override;

private:
    GameScene* _scene;
};

END_NS_SCENES
#endif /* LOCALBATTLECONTROLLER_H */
