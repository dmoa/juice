#pragma once

#include <Engine/Engine.h>

#include "utils/GetGameController.h"

// Mouse Functions

// For uniformity
#define GetMouseState SDL_GetMouseState
#define JOYSTICK_LEFTX SDL_CONTROLLER_AXIS_LEFTX
#define JOYSTICK_LEFTY SDL_CONTROLLER_AXIS_LEFTY
#define JOYSTICK_RIGHTX SDL_CONTROLLER_AXIS_RIGHTX
#define JOYSTICK_RIGHTY SDL_CONTROLLER_AXIS_RIGHTY

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


// Mouse

inline void GetMouseGameState(int* x, int* y) {
    SDL_GetMouseState(x, y);
    if (x) *x = *x / g_window.scale + g_window.gameplay_viewport.x;
    if (y) *y = *y / g_window.scale + g_window.gameplay_viewport.y;
}

inline bool GetMouseDown(int i = 1) { return SDL_GetMouseState(NULL, NULL) == SDL_BUTTON(i); };


// Joystick

// Functions with same functionality, but the names makes it slightly clearer when running them.
inline bool IsLeft(s16 value) { return value < - AXIS_MIN; };
inline bool IsRight(s16 value) { return value > AXIS_MIN; };
inline bool IsUp(s16 value) { return value < - AXIS_MIN; };
inline bool IsDown(s16 value) { return value > AXIS_MIN; };

inline s16 ControllerAxis(SDL_GameControllerAxis button) { return SDL_GameControllerGetAxis(g_controls.controller, button); }
inline bool ControllerButton(SDL_GameControllerButton button) { return SDL_GameControllerGetButton(g_controls.controller, button); }


#ifdef ENGINE_IMPLEMENTATION

void GlobalControls::Init() {
    keys_down = SDL_GetKeyboardState(NULL);
    controller = GetGameController();
}

bool GlobalControls::Left() {
    return keys_down[SDL_SCANCODE_LEFT] || keys_down[SDL_SCANCODE_A] || IsLeft(ControllerAxis(JOYSTICK_LEFTX));
}

bool GlobalControls::Right() {
    return keys_down[SDL_SCANCODE_RIGHT] || keys_down[SDL_SCANCODE_D] || IsRight(ControllerAxis(JOYSTICK_LEFTX));
}

bool GlobalControls::Up() {
    return keys_down[SDL_SCANCODE_UP] || keys_down[SDL_SCANCODE_W] || IsUp(ControllerAxis(JOYSTICK_LEFTY));
}

bool GlobalControls::Down() {
    return keys_down[SDL_SCANCODE_DOWN] || keys_down[SDL_SCANCODE_S] || IsDown(ControllerAxis(JOYSTICK_LEFTY));
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