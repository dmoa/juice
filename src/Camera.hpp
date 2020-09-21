#pragma once

#include "sdl.h"

#include "utils/Controls.hpp"

#include "GlobalWindowData.hpp"
#include "Player.hpp"
#include "Map.hpp"

struct Camera {
public:
    void GivePlayerMapDelta(Player* _player, Map* _map, float* _dt);
    SDL_Rect* GetViewport();
    void Update();
    void DevUpdate();
private:
    Player* player;
    Map* map;
    float* dt;

    float real_x = 0.f;
    float real_y = 0.f;
    SDL_Rect viewport = {real_x, real_y, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};

    float pan_v = 400;
};