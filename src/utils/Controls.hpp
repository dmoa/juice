#pragma once

#include <SDL2/SDL.h>

#include "GetGameController.hpp"

namespace CTS {
    bool Left();
    bool Right();
    bool Up();
    bool Down();
    bool Action1();

    void LoadInput();
    extern const Uint8* keys_down;
    extern SDL_GameController* controller;
    // minimum angle for axis to be considered "moved"
    extern const int axis_min;
}