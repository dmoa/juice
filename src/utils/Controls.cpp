#include "Controls.hpp"

namespace CTS {
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
        return keys_down[SDL_SCANCODE_SPACE];
    }

    void LoadInput() {
        keys_down = SDL_GetKeyboardState(NULL);
        controller = GetGameController();
    }
    const Uint8* keys_down = NULL;
    SDL_GameController* controller = NULL;
    const int axis_min = 12000;
};