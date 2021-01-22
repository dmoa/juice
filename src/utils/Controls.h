#pragma once

#include <Engine/Engine.h>

#include "GetGameController.h"

namespace CTS {
    extern const Uint8* keys_down;
    extern SDL_GameController* controller;
    extern const int axis_min;
    void Init();
    bool Left();
    bool Right();
    bool Up();
    bool Down();
    bool Action1();
    bool ActionDev();
}

#ifdef CONTROLS_IMPLEMENTATION

inline s16 ControllerAxis(SDL_GameControllerAxis button) { return SDL_GameControllerGetAxis(CTS::controller, button); }
inline bool ControllerButton(SDL_GameControllerButton button) { return SDL_GameControllerGetButton(CTS::controller, button); }

namespace CTS {
    const Uint8* keys_down;
    SDL_GameController* controller;
    // minimum angle for axis to be considered "moved"
    const int axis_min = 14000;

    bool action_dev_before = false;

    void Init() {
        keys_down = SDL_GetKeyboardState(NULL);
        controller = GetGameController();
    }

    bool Left() {
        return keys_down[SDL_SCANCODE_LEFT] || keys_down[SDL_SCANCODE_A] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) < - axis_min;
    }
    bool Right() {
        return keys_down[SDL_SCANCODE_RIGHT] || keys_down[SDL_SCANCODE_D] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) > axis_min;
    }
    bool Up() {
        return keys_down[SDL_SCANCODE_UP] || keys_down[SDL_SCANCODE_W] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) < - axis_min;
    }
    bool Down() {
        return keys_down[SDL_SCANCODE_DOWN] || keys_down[SDL_SCANCODE_S] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) > axis_min;
    }
    bool Action1() {
        return GetMouseDown(SDL_BUTTON_LEFT) || ControllerButton(SDL_CONTROLLER_BUTTON_X);
    }
    bool ActionDev() {
        bool action_dev_now = (keys_down[SDL_SCANCODE_LCTRL]) || (ControllerButton(SDL_CONTROLLER_BUTTON_BACK) && CTS::Left());
        bool result = action_dev_now && ! action_dev_before;
        action_dev_before = action_dev_now;

        return result;
    }
};

#endif