#pragma once

#include <SDL2/SDL_gamecontroller.h>

inline SDL_GameController* GetGameController() {

    SDL_GameController* controller = NULL;

    // go through every joystick attatched to the computer
    SDL_Log("Num controllers connected: %i", SDL_NumJoysticks());
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        // is it supported by sdl?
        if (SDL_IsGameController(i)) {

            // then set the controller to this joystick
            controller = SDL_GameControllerOpen(i);

            // if it managed to set it, exit the function
            if (controller) {
                return controller;
            }
            // otherwise, throw error that the game controller couldn't attatch to the joystick
            else {
                SDL_Log("Could not open SDL gamecontroller: %s\n", SDL_GetError());
            }
        }
    }

    if (!controller) SDL_Log("Controller not found");

    return NULL;
}