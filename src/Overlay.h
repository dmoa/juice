#pragma once

#include <Engine/Engine.h>

#include "Player.h"

struct SimpleAsset {
    SDL_Rect drect;
    Asset_Ase* asset;
};

struct Overlay {

    void GivePointers(Player* _player);
    void LoadAssets();
    void DestroyAssets();
    void Draw();
    void Update();

    Player* player;

    SimpleAsset heart;
    SimpleAsset health_bar;
    SimpleAsset red_bar;

};