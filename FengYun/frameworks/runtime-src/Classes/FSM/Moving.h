/**
 * @file  Moving.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_MOVING_H
#define FSM_MOVING_H

#include "BaseState.h"

BEGIN_NS_FSM

class Moving : public BaseState
{
public:
    Moving();
    virtual ~Moving();

    bool isRunning() const { return _isRunning; }
    void startRun();

    const Vector2& getAxis() const { return _axis; }
    void setAxis(const Vector2& axis) { _axis = axis; }

protected:
    void onEnter() override;
    void onExit() override;
    void onDidUpdate() override;

private:
    bool _isRunning;
    Vector2 _axis;
};


END_NS_FSM
#endif /* FSM_MOVING_H */
