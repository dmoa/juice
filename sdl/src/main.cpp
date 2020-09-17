#pragma once

#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "utils/Controls.hpp"
#include "utils/Text.hpp"
#include "utils/Clock.cpp"
#include "utils/PrintOnScreen.hpp"

#include "Window.hpp"
#include "GlobalWindowData.hpp"
#include "Camera.hpp"

#include "ECS/ECS.hpp"

#include "Player.hpp"
#include "Map.hpp"
#include "Enemies.hpp"

GlobalWindowData global_window_data = {640, 640, 4, NULL};

// @TODO
// Seperate UpdateAnimation Function which takes pointers to timer, current_animation, current_frame, type.
// Set Animation Function as well.

int main(int argc, char* argv[]) {
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    Text::LoadFont();
    CTS::LoadInput();
    srand(time(0));

    bool DEV_PAUSED = false;

    PrintOnScreen print;
    Window window;
    Clock clock;
    Camera gameplay_camera;
    ECS ecs;
    Player player;
    Map map;
    Enemies enemies;

    gameplay_camera.GivePlayerMapDelta(& player, & map, & clock.dt);

    ecs.GiveMapPlayerEnemies(& map, & player, & enemies);

    player.LoadTexture();
    player.GiveMapDeltaECS(& map, & clock.dt, & ecs);
    player.InitPos();

    map.LoadTexture();
    map.GivePlayerDeltaECS(& player, & clock.dt, & ecs);
    map.CreateMapTexture();
    map.CreateCollisionBoxes();

    enemies.CreateTextures();
    enemies.GiveDeltaMap(& clock.dt, & map);
    enemies.CreateEnemies();

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
                    if (event.key.keysym.sym == SDLK_ESCAPE) quit = true;
                    if (event.key.keysym.sym == SDLK_LCTRL)  DEV_PAUSED = ! DEV_PAUSED;
                    if (event.key.keysym.sym == SDLK_r)      map.ReloadTilesetTexture();
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
            enemies.Update();
            gameplay_camera.Update();
        }


        // DRAW

        window.Clear();

        window.SetDrawGameplay();

        map.DrawBase();
        ecs.Draw();

        window.SetDrawOther();

        print.Draw(std::to_string( clock.average_fps ), 2, 0);
        print.Draw("Hello Sailor!", 2, 10);

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