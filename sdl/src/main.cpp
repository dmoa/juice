#pragma once

#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "utils/Controls.hpp"
#include "utils/Text.hpp"
#include "utils/Clock.cpp"
#include "utils/PrintOnScreen.hpp"
#include "utils/AABB.hpp"

#include "Window.hpp"
#include "GlobalWindowData.hpp"
#include "Camera.hpp"

#include "objects/ObjectsInfo.hpp"
#include "objects/SOAObjects.hpp"
#include "objects/ObjectsNames.hpp"

#include "Player.hpp"
#include "Map.hpp"
#include "Enemies.hpp"

GlobalWindowData global_window_data = {640, 640, 4, NULL};

void AddObject(Objects* objects, float x, float y, OBJECT_NAMES name) {

    int i = objects->xs.size() - 1;
    while (i > 0) {
        if (AABB(x, y, OBJECTS_QUAD_DIMENSIONS.ws[name], OBJECTS_QUAD_DIMENSIONS.hs[name], objects->xs[i], objects->ys[i], OBJECTS_QUAD_DIMENSIONS.ws[objects->names[i]], OBJECTS_QUAD_DIMENSIONS.hs[objects->names[i]]) && y + OBJECTS_COLLISION_INFO.ys[name] + OBJECTS_COLLISION_INFO.hs[name] > objects->ys[i] + OBJECTS_COLLISION_INFO.ys[objects->names[i]] + OBJECTS_COLLISION_INFO.hs[objects->names[i]]) {
            break;
        }
        i --;
    }

    i ++;

    objects->xs.insert(objects->xs.begin() + i, 0.f);
    objects->ys.insert(objects->ys.begin() + i, 0.f);
    objects->names.insert(objects->names.begin() + i, name);
}

Objects SortObjects(Map* map, Player* player, Enemies* enemies) {
    Objects objects = map->objects;

    AddObject(& objects, player->x, player->y, PLAYER);

    return objects;
}

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

        Objects objects = SortObjects(& map, & player, & enemies);

        // DRAW

        window.Clear();

        window.SetDrawGameplay();

        map.DrawBase();
        for (unsigned int i = 0; i < objects.xs.size(); i++) {

            OBJECT_NAMES name = objects.names[i];

           if (name == PLAYER) {
                player.Draw();
            } else {
                map.DrawObject(objects.xs[i], objects.ys[i], name);
            }

        }
        enemies.Draw();

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