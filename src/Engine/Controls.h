#pragma once

#include <Engine/Engine.h>

#include "utils/GetGameController.h"

// Mouse Functions

inline void GetMouseGameState(int* x, int* y) {
    SDL_GetMouseState(x, y);
    if (x) *x = *x / g_window.scale + g_window.gameplay_viewport.x;
    if (y) *y = *y / g_window.scale + g_window.gameplay_viewport.y;
}

inline u32 GetMouseDown(int i) { return SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(i); };

// Keyboard

// minimum angle for axis to be considered "moved"
#define AXIS_MIN 14000

struct GlobalControls {
    const Uint8* keys_down = NULL;
    SDL_GameController* controller = NULL;
    bool action_dev_before = false;
    void Init();
    bool Left();
    bool Right();
    bool Up();
    bool Down();
    bool Action1();
    bool ActionDev();
};
extern GlobalControls g_controls;


#ifdef ENGINE_IMPLEMENTATION

inline s16 ControllerAxis(SDL_GameControllerAxis button) { return SDL_GameControllerGetAxis(g_controls.controller, button); }
inline bool ControllerButton(SDL_GameControllerButton button) { return SDL_GameControllerGetButton(g_controls.controller, button); }

void GlobalControls::Init() {
    keys_down = SDL_GetKeyboardState(NULL);
    controller = GetGameController();
}

bool GlobalControls::Left() {
    return keys_down[SDL_SCANCODE_LEFT] || keys_down[SDL_SCANCODE_A] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) < - AXIS_MIN;
}

bool GlobalControls::Right() {
    return keys_down[SDL_SCANCODE_RIGHT] || keys_down[SDL_SCANCODE_D] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) > AXIS_MIN;
}

bool GlobalControls::Up() {
    return keys_down[SDL_SCANCODE_UP] || keys_down[SDL_SCANCODE_W] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) < - AXIS_MIN;
}

bool GlobalControls::Down() {
    return keys_down[SDL_SCANCODE_DOWN] || keys_down[SDL_SCANCODE_S] || ControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) > AXIS_MIN;
}

bool GlobalControls::Action1() {
    return GetMouseDown(SDL_BUTTON_LEFT) || ControllerButton(SDL_CONTROLLER_BUTTON_X);
}

bool GlobalControls::ActionDev() {
    // To make sure the function doesn't constantly spam ActionDev is down.
    // It acts more as a key down event.
    bool action_dev_now = (keys_down[SDL_SCANCODE_LCTRL]) || (ControllerButton(SDL_CONTROLLER_BUTTON_BACK) && g_controls.Left());
    bool result = action_dev_now && ! action_dev_before;
    action_dev_before = action_dev_now;

    return result;
}

GlobalControls g_controls;

#endif