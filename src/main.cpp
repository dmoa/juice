#pragma once

#include <time.h>
#include <stdio.h>

#define ENGINE_IMPLEMENTATION
#include <Engine/Engine.h>

#include "Camera.h"

#include "ECS/ECS.h"

#include "Player.h"
#include "Map.h"
#include "Enemies.h"
#include "Crosshair.h"

int main(int argc, char* argv[]) {
    EngineInit();
    window.Init();

    bool DEV_PAUSED = false;

    Camera gameplay_camera;
    ECS ecs;
    Player player;
    Map map;
    Enemies enemies;
    Crosshair crosshair;


    gameplay_camera.PassPointers(& player, & map, & g_dt);

    ecs.GivePointers(& map, & player, & enemies);

    player.LoadAsset();
    player.PassPointers(& map, & enemies, & ecs, & g_dt);
    player.InitPos();

    map.LoadAssets();
    map.PassPointers(& player, & g_dt, & ecs);
    map.CreateMapTexture();
    map.CreateCollisionBoxes();

    crosshair.LoadAsset();

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
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_r:
                            map.DestroyAssets();
                            map.LoadAssets();
                            player.DestroyAsset();
                            player.LoadAsset();
                            crosshair.DestroyAsset();
                            crosshair.LoadAsset();
                            break;
                        default: break;
                    }
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        g_window.w = event.window.data1;
                        g_window.h = event.window.data2;
                    }
                    break;
                default: break;
            }
        }

        if (g_controls.ActionDev()) DEV_PAUSED = ! DEV_PAUSED;

        engine_clock.tick();

        if (DEV_PAUSED) {
            gameplay_camera.DevUpdate();
        } else {
            player.Update();
            map.Update();
            enemies.Update();
            gameplay_camera.Update();
            crosshair.Update();
        }
        SDL_ShowCursor(DEV_PAUSED); // if in dev mode -> show cursor

        // DRAW

        window.Clear();

        window.SetDrawGameplay();

        map.DrawBase();
        ecs.Draw();
        crosshair.Draw();

        window.SetDrawOther();

        PrintScreen(std::to_string( engine_clock.average_fps ), 2, 0);

        window.Present();
    }

    player.DestroyAsset();
    map.DestroyTextures();
    window.Shutdown();
    EngineQuit();
    return 0;
}