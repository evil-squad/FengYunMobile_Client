/**
 * @file  UserInputProcessor.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/1.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "UserInputProcessor.h"
#include "GameInput.h"
#include "Physics.h"

#include "Standing.h"
#include "Moving.h"

#include "GameApp.h"

USING_NS_ECS;

BEGIN_NS_FSM

static const float FirstHeight = 224;
static const float HoriJumpSpeed = 320;
static const int JumpPrority = 10;

static inline Vector2 getInputVelocity(GameInput* input)
{
    auto data = input->getAxis(input->getAxisId("Joystick"));
    if (data)
        return data->axis;
    return Vector2::ZERO;
}

static inline JoystickDir getJoystickDir(GameInput* input)
{
    auto data = input->getAxis(input->getAxisId("Joystick"));
    if (data)
        return data->dir;
    return JoystickDir::NONE;
}

static inline float calcVertSpeed(float height)
{
    return sqrtf(2 * height * Physics::gravity());
}

static inline Vector2 calcJumpSpeed(JoystickDir dir, int jumpCount)
{
    Vector2 speed;
    speed.y = calcVertSpeed(FirstHeight);

    switch (dir)
    {
        case JoystickDir::LEFT:
            speed.x = -1;
            break;
        case JoystickDir::RIGHT:
            speed.x = 1;
            break;
        default:
            speed.x = 0;
            break;
    }

    return speed;
}

UserInputProcessor::UserInputProcessor(Fsm* fsm, BaseData* fsmData)
    : BaseInputProcessor(fsm, fsmData)
    , _joystickEnabled(true)
    , _jumpEnabled(true)
    , _attackEnabled(true)
    , _skillEnabled(true)
    , _inputAxis(Vector2::ZERO)
    , _joystickDir(JoystickDir::NONE)
    , _attackAxis(Vector2::ZERO)
    , _attackPressedTime(-1)
    , _mover(nullptr)
    , _job(RoleJob::NONE)
    , _nextState(nullptr)
{
    _mover = new UserFreeMover();

    _job = RoleJob::BUJINGYUN;
}

UserInputProcessor::~UserInputProcessor()
{
    delete _mover;
}

bool UserInputProcessor::isInputEnabled(fy::fsm::InputType type)
{
    switch (type)
    {
        case InputType::ALL:
            return _joystickEnabled && _jumpEnabled && _attackEnabled && _skillEnabled;
        case InputType::JOYSTICK:
            return _joystickEnabled;
        case InputType::JUMP:
            return _jumpEnabled;
        case InputType::ATTACK:
            return _attackEnabled;
        case InputType::SPECIAL_SKILL:
            return _skillEnabled;
        default:
            return false;
    }
}

void UserInputProcessor::setInputEnabled(fy::fsm::InputType type, bool value)
{
    switch (type)
    {
        case InputType::ALL:
            _joystickEnabled = value;
            _jumpEnabled = value;
            _attackEnabled = value;
            _skillEnabled = value;
            if (!value)
                _attackPressedTime = -1;
            break;
        case InputType::JOYSTICK:
            _joystickEnabled = value;
            break;
        case InputType::JUMP:
            _jumpEnabled = value;
            break;
        case InputType::ATTACK:
            _attackEnabled = value;
            if (!value)
                _attackPressedTime = -1;
            break;
        case InputType::SPECIAL_SKILL:
            _skillEnabled = value;
            break;
        default:
            break;
    }
}

void UserInputProcessor::update(fy::fsm::BaseState *st)
{
    auto input = GameInput::getInstance();
    auto role = st->getRole();

    if (_joystickEnabled)
    {
        _inputAxis = getInputVelocity(input);
        _joystickDir = getJoystickDir(input);
    }
    else
    {
         _inputAxis = Vector2::ZERO;
        _joystickDir = JoystickDir::NONE;
    }

    float time = _fsm->getTime();

    if (_skillEnabled)
        if (processSkills(st, input, time)) return;
    if (_attackEnabled)
        if (processAttack(st, input, time)) return;
    if (_jumpEnabled)
        if (processJump(st, input, time)) return;

    if (st->getName() == "Standing")
    {
        if (!_inputAxis.isZero())
        {
            _mover->setAxis(_inputAxis);
            st->notifyInterrupted(get_state<BaseState>(_fsm, "Moving"));
        }
    }

    if (st->getName() == "Moving")
    {
        auto move = static_cast<Moving*>(st);
        move->setAxis(_inputAxis);
        move->setDir(_joystickDir);
        _mover->setAxis(_inputAxis);
    }

    if (st->isSkill())
    {

    }
}

BaseMover* UserInputProcessor::getFreeMover()
{
    return _mover;
}

void UserInputProcessor::onHandleAgentMsg(net::AgentMsg msg)
{
    auto curState = getCurrentState();

    switch (msg.getType())
    {
        case net::AgentMsgType::MOVE:
        {
            auto role = _fsmData->getRole();
            auto d = &msg.as<net::AgentMoveData>();
            auto pt = Vector3(d->posX, d->posY, d->posZ);

            onMove(true, d->step);

            if (curState && !curState->isSkill())
            {
                auto m = get_state<Moving>(_fsm, "Moving");
                if (!m->isRunning()) m->startRun();
            }

            auto trans = _fsmData->getRole()->getTransform();
            auto curMapPos = trans->getPosition();
            auto diff = pt - curMapPos;
            if (diff.lengthSquared() > 2 * 2 * 2)
            {
                auto pos = pt;
                trans->setPosition(pos);
            }
        }
            break;

        default:
            break;
    }
}

void UserInputProcessor::onCastSkill(int skillId)
{
    BaseInputProcessor::onCastSkill(skillId);
}

bool UserInputProcessor::processAttack(fy::fsm::BaseState *st, fy::GameInput *input, float time)
{
    int attackBtnId = input->getButtonId("Attack");
    if (input->getButtonDown(attackBtnId))
    {
        _attackPressedTime = time;
    }
    if (_attackPressedTime < 0) return false;

    return false;
}

bool UserInputProcessor::processJump(fy::fsm::BaseState *st, fy::GameInput *input, float time)
{
    return false;
}
bool UserInputProcessor::processSkills(fy::fsm::BaseState *st, fy::GameInput *input, float time)
{
    return false;
}

bool UserInputProcessor::doCastSkill(fy::fsm::BaseState *st, int skillId)
{
    return false;
}

void UserInputProcessor::doGroundAttack(fy::fsm::BaseState *st, JoystickDir dir, bool isShort)
{

}

void UserInputProcessor::doAirAttack(fy::fsm::BaseState *st, JoystickDir dir, bool isShort)
{

}


END_NS_FSM












