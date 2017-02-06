/**
 * @file  Dead.hpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/6.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef FSM_DEAD_H
#define FSM_DEAD_H

#include "BaseState.h"

BEGIN_NS_FSM

class Dead : public BaseState
{
public:
    Dead();
    ~Dead();

    bool isDead() const { return _dead; }
    void setDeadCallback(std::function<void()>& cb) { _deadCallback = cb; }

protected:
    void onEnter() override;
    void onExit() override;
    void onDidUpdate() override;

private:
    bool _dead;

    std::function<void()> _deadCallback;
};

END_NS_FSM
#endif /* FSM_DEAD_H */
