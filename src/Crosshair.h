#pragma once

#include <Engine/Engine.h>

struct Player;

struct Crosshair {

    void GivePointers(Player* _player);
    void LoadAsset();
    void DestroyAsset();
    void Draw();
    void Update();

    Player* player;

    SDL_Texture* texture;
    SDL_Rect render_rect = {100, 100, -1, -1};
    bool is_drawn = true;
    // Was the last movement with the crosshair done with a controller?
    bool last_move_with_controller = false;

    // center of the crosshair
    float x = 100;
    float y = 100;

    // The distance from the player to the crosshair when
    // controlling the crosshair with a controller.
    float controller_crosshair_r = 23;
};