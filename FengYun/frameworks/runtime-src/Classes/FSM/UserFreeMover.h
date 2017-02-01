/**
 * @file  UserFreeMover.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/1/31.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_USERFREEMOVER_H
#define FSM_USERFREEMOVER_H

#include "BaseMover.h"
#include "MathTypes.h"
#include "DebugHelper.h"

BEGIN_NS_FSM

class UserFreeMover : public BaseMover
{
public:
    UserFreeMover();
    virtual ~UserFreeMover();

    const Vector2& getAxis() const { return _axis; }
    void setAxis(const Vector2& axis) { _axis = axis; }

    void enter(BaseState* st) override;
    void exit(BaseState* st) override;
    void update(BaseState* st) override;

private:
    bool _isNormalMoving;
    bool _running;
    bool _serverMoving;
    float _speed;
    float _time;
    Vector2 _axis;
    Vector2 _adjustAxis;
    Vector2 _lastAdjustAxis;
    Vector3 _predictPoint;

    void updatePredicts(BaseState* st, bool force = false);
    void adjustAxis(BaseState* st, float dt);
    void updateSpeed(BaseState* st);
};

END_NS_FSM
#endif /* FSM_USERFREEMOVER_H */
