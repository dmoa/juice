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
#include "Overlay.h"

int main(int argc, char* argv[]) {
    EngineInit();
    window.Init();
    // To give some legit old_mouse coords before running MouseMoved in the wild. Otherwise, MouseMoved can give the wrong answer.
    g_controls.MouseMoved();

    bool DEV_PAUSED = false;

    Camera gameplay_camera;
    ECS ecs;
    Player player;
    Map map;
    Enemies enemies;
    Crosshair crosshair;
    Overlay overlay;

    gameplay_camera.PassPointers(& player, & map, & g_dt);

    ecs.Init();

    player.PassPointers(& map, & enemies, & ecs, & crosshair);
    player.LoadAsset();
    player.InitPos();

    map.PassPointers(& player, & g_dt, & ecs);
    map.LoadAssets();
    map.CreateMapTexture();
    map.CreateCollisionBoxes();

    enemies.GivePointers(& ecs, & player);
    enemies.LoadAssets();
    enemies.InitAllEnemies();

    crosshair.GivePointers(& player);
    crosshair.LoadAsset();

    overlay.GivePointers(& player);
    overlay.LoadAssets();

    free(NULL);

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
                        case SDLK_r:
                            map.DestroyAssets();
                            map.LoadAssets();
                            player.DestroyAsset();
                            player.LoadAsset();
                            player.current_health = player.max_health;
                            crosshair.DestroyAsset();
                            crosshair.LoadAsset();
                            overlay.DestroyAssets();
                            overlay.LoadAssets();
                            break;
                        default: break;
                    }
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        g_window.w = event.window.data1;
                        g_window.h = event.window.data2;
                    }
                    break;

                case SDL_CONTROLLERDEVICEADDED:
                    g_controls.controller = GetGameController();
                    break;

                case SDL_CONTROLLERDEVICEREMOVED:
                    FreeGameController(g_controls.controller);
                    g_controls.controller = NULL;
                    break;

                default: break;
            }
        }

        if (g_controls.ActionDev()) DEV_PAUSED = ! DEV_PAUSED;
        if (g_controls.Back()) quit = true;

        engine_clock.tick();

        if (DEV_PAUSED) {
            gameplay_camera.DevUpdate();
        } else {
            player.Update();
            map.Update();
            enemies.Update();
            gameplay_camera.Update();
            crosshair.Update();
            overlay.Update();

            player.FinishUpdate();

            ecs.Update();
        }
        SDL_ShowCursor(DEV_PAUSED); // if in dev mode -> show cursor

        // DRAW

        window.Clear();

        window.SetDrawGameplay();

        map.DrawBase();
        ecs.Draw();
        crosshair.Draw();

        window.SetDrawOther();

        overlay.Draw();

        window.Present();
    }


    player.DestroyAsset();
    map.DestroyTextures();
    map.DestroyAssets();
    crosshair.DestroyAsset();
    overlay.DestroyAssets();

    window.Shutdown();
    EngineQuit();
    return 0;
}