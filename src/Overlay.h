#pragma once

#include <Engine/Engine.h>

#include "Player.h"

struct Overlay {

    void GivePointers(Player* _player);
    void LoadAssets();
    void DestroyAssets();
    void Draw();
    void Update();

    Player* player;

    SDL_Rect heart_drect;
    SDL_Rect health_bar_drect;

    Asset_Ase* heart_asset;
    Asset_Ase* health_bar_asset;
};