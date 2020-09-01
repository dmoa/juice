#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "utils/Controls.hpp"
#include "utils/Text.hpp"
#include "utils/Clock.cpp"

#include "Window.hpp"
#include "GlobalWindowData.hpp"
#include "Camera.hpp"

#include "Player.hpp"
#include "Map.hpp"
#include "Enemies.hpp"

GlobalWindowData global_window_data = {640, 640, 4, NULL};

int main(int argc, char* argv[]) {
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Text::LoadFont();
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    CTS::LoadInput();
    srand(time(0));

    bool DEV_PAUSED = false;

    Window window;
    Clock clock;
    Camera gameplay_camera;
    Player player;
    Map map;
    Enemies enemies;

    gameplay_camera.GivePlayerMapDelta(& player, & map, & clock.dt);

    player.LoadTexture();
    player.GiveMapDelta(& map, & clock.dt);

    map.LoadTexture();
    map.GivePlayerDelta(& player, & clock.dt);
    map.CreateMapTexture();
    map.CreateCollisionBoxes();

    enemies.CreateTextures();
    enemies.GiveDelta(& clock.dt);

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
                    if (event.key.keysym.sym == SDLK_LCTRL)
                        DEV_PAUSED = ! DEV_PAUSED;
                    if (event.key.keysym.sym == SDLK_r) {
                        map.ReloadTilesetTexture();
                    }
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        global_window_data.w = event.window.data1;
                        global_window_data.h = event.window.data2;
                    }
                    break;
                default: break;
            }
        }

        clock.tick();

        if (DEV_PAUSED) {
            gameplay_camera.DevUpdate();
        } else {
            player.Update();
            map.Update();
            gameplay_camera.Update();
        }


        // DRAW

        window.Clear();

        window.SetDrawGameplay();

        map.DrawFirst();
        player.Draw();
        map.DrawSecond();
        enemies.Draw();

        window.SetDrawOther();

        window.Present(gameplay_camera.GetViewport());
    }

    player.DestroyTexture();
    map.DestroyTextures();

    Text::DestroyFont();
    TTF_Quit();
    IMG_Quit();
    window.Shutdown();
    SDL_Quit();
    return 0;
}