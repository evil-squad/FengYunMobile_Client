/**
 * @file  GameInput.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "GameInput.h"
#include "DebugHelper.h"
#include "cocos2d.h"

USING_NS_CC;

BEGIN_NS_FY

GameInput* GameInput::getInstance()
{
    static GameInput* instance = nullptr;
    if (!instance)
    {
        instance = new GameInput();
        Director::getInstance()->getScheduler()->scheduleUpdate(instance, Scheduler::PRIORITY_NON_SYSTEM_MIN, false);
    }
    return instance;
}

GameInput::GameInput()
{
}

GameInput::~GameInput()
{
}

static int s_idCounter = 0;

int GameInput::getAxisId(const std::string &name)
{
    auto iter = _ids.find(name);
    if (iter != _ids.end()) return iter->second;
    _ids[name] = ++ s_idCounter;
    return s_idCounter;
}

int GameInput::getButtonId(const std::string &name)
{
    auto iter = _ids.find(name);
    if (iter != _ids.end()) return iter->second;
    _ids[name] = ++s_idCounter;
    return s_idCounter;
}

void setAxis(std::unordered_map<int, float>& axis, int axisId, float val)
{
    auto iter = axis.find(axisId);
    if (iter != axis.end())
        iter->second = val;
    else
        axis[axisId] = val;
}

template <typename T>
void setButton(std::unordered_map<int, T>& buttons, int btnId, bool pressed)
{
    auto iter = buttons.find(btnId);
    if (iter != buttons.end())
    {
        if (pressed != iter->second.pressed)
        {
            iter->second.pressed = pressed;

            if (pressed)
                iter->second.isDown = true;
            else
                iter->second.isUp = true;
        }
    }
    else
    {
        if (pressed)
            buttons[btnId] = T{ true, true, false };
        else
            buttons[btnId] = T{ true, false, false };
    }
}

void GameInput::addInputEvent(int id, float value)
{
    InputEvent event;
    event.type = InputEventType::AXIS_EVENT;
    event.axisEvent.id = id;
    event.axisEvent.value = value;
    _eventQue.push(event);
}

void GameInput::addInputEvent(int id, bool value)
{
    InputEvent event;
    event.type = InputEventType::BUTTON_EVENT;
    event.buttonEvent.id = id;
    event.buttonEvent.value = value;
    _eventQue.push(event);
}

void GameInput::update(float dt)
{
    if (Director::getInstance()->isPaused()) return;

    for (auto& iter: _buttons)
    {
        iter.second.isDown = false;
        iter.second.isUp = false;
    }

    while (!_eventQue.empty())
    {
        auto &ev = _eventQue.front();
        if (ev.type == InputEventType::AXIS_EVENT)
        {
            setAxis(_axis, ev.axisEvent.id, ev.axisEvent.value);
        }
        else if (ev.type == InputEventType::BUTTON_EVENT)
        {
            setButton(_buttons, ev.buttonEvent.id, ev.buttonEvent.value);
        }
        else
        {
            DBG_LOG("GameInput: unsupport event type!");
        }
        _eventQue.pop();
    }
}

END_NS_FY
