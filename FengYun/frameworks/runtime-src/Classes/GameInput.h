/**
 * @file  GameInput.h
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 12/01/2017.
 * @  Copyright © 2017 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#ifndef GAMEINPUT_H
#define GAMEINPUT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

#include "gamebase.h"

BEGIN_NS_FY

enum class InputEventType
{
    AXIS_EVENT = 1,
    BUTTON_EVENT
};

class GameInput
{
public:
    static GameInput* getInstance();

    void addInputEvent(int id, float value);
    void addInputEvent(int id, bool value);

    int getAxisId(const std::string& name);
    int getButtonId(const std::string& name);

    float getAxis(int axisId)
    {
        if (axisId == 0) return 0;
        auto iter = _axis.find(axisId);
        if (iter != _axis.end())
            return iter->second;
        else
            return 0;
    }

    bool getButtonDown(int btnId)
    {
        if (btnId == 0) return false;
        auto iter = _buttons.find(btnId);
        if (iter != _buttons.end())
            return iter->second.isDown;
        else
            return false;
    }

    bool getButtonUp(int btnId)
    {
        if (btnId == 0) return false;
        auto iter = _buttons.find(btnId);
        if (iter != _buttons.end())
            return iter->second.isUp;
        else
            return false;
    }

    void update(float dt);

private:
    GameInput();
    ~GameInput();

private:
    struct ButtonData_t
    {
        bool pressed;
        bool isDown, isUp;
    };

    union InputEvent
    {
        InputEventType type;
        struct
        {
            InputEventType type;
            int id;
            float value;
        }axisEvent;

        struct
        {
            InputEventType type;
            int id;
            bool value;
        }buttonEvent;
    };

    std::queue<InputEvent> _eventQue;
    std::unordered_map<std::string, int> _ids;
    std::unordered_map<int, float> _axis;
    std::unordered_map<int, ButtonData_t>_buttons;
};

END_NS_FY
#endif /* GAMEINPUT_H */
