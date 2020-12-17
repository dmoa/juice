#pragma once

#include <SDL_CP.h>

#include "../utils/GetGameController.h"

namespace CTS {
    extern const Uint8* keys_down;
    extern SDL_GameController* controller;
    extern const int axis_min;
    bool Left();
    bool Right();
    bool Up();
    bool Down();
    bool Action1();
}

#ifdef CONTROLS_IMPLEMENTATION

namespace CTS {
    const Uint8* keys_down = SDL_GetKeyboardState(NULL);
    SDL_GameController* controller = GetGameController();
    // minimum angle for axis to be considered "moved"
    const int axis_min = 14000;

    bool Left() {
        return keys_down[SDL_SCANCODE_LEFT] || keys_down[SDL_SCANCODE_A] || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) < - axis_min;
    }
    bool Right() {
        return keys_down[SDL_SCANCODE_RIGHT] || keys_down[SDL_SCANCODE_D] || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX) > axis_min;
    }
    bool Up() {
        return keys_down[SDL_SCANCODE_UP] || keys_down[SDL_SCANCODE_W] || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) < - axis_min;
    }
    bool Down() {
        return keys_down[SDL_SCANCODE_DOWN] || keys_down[SDL_SCANCODE_S] || SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY) > axis_min;
    }
    bool Action1() {
        // @TODO
        // add A button for controller here
        return keys_down[SDL_SCANCODE_SPACE] || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
    }
};

#endif