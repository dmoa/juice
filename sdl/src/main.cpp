#pragma once

#include <iostream>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Window.hpp"
#include "GlobalWindowData.hpp"
#include "Text.hpp"
#include "Clock.cpp"

#include "Player.hpp"

GlobalWindowData global_window_data = {500, 500, NULL, SDL_GetKeyboardState(NULL)};

int main(int argc, char* argv[]) {
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Text::LoadFont();

    Window window;
    Clock clock;
    Player player;
    player.LoadTexture();
    player.GiveDT(& clock.dt);

    SDL_Event event;
    bool quit = false;
    while (!quit) {

        // UPDATE

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;
                    break;
                default: break;
            }
        }
        clock.tick();

        player.Update();


        // DRAW

        window.Clear();

        player.Draw();

        SDL_RenderPresent(global_window_data.rdr);
    }

    Text::DestroyFont();
    TTF_Quit();
    IMG_Quit();
    window.Shutdown();
    SDL_Quit();
    return 0;
}