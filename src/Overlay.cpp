#include "Overlay.h"

void Overlay::GivePointers(Player* _player) {
    player = _player;
}

void Overlay::LoadAssets() {

    heart.asset = LoadAsset_Ase("assets/heart.ase");
    health_bar.asset = LoadAsset_Ase("assets/empty_health_bar.ase");
    red_bar.asset = LoadAsset_Ase("assets/red_bar.ase");

    heart.drect.x = heart.drect.y = 5;

    // red_bar is going to be directly over the health_bar, which is why it has the same coordinates.
    health_bar.drect.x = red_bar.drect.x = heart.drect.x + heart.asset->frame_width + 5;
    health_bar.drect.y = red_bar.drect.y = heart.drect.y + heart.asset->frame_height / 2 - health_bar.asset->frame_height / 2;

    // We use SDL_RenderCopy for red_bar in Draw, so we need to define drect height as it is not filled automatically (like in RenderCopyWhole)
    red_bar.drect.h = red_bar.asset->frame_height;
}

void Overlay::DestroyAssets() {
    DestroyAsset_Ase(heart.asset);
    DestroyAsset_Ase(health_bar.asset);
    DestroyAsset_Ase(red_bar.asset);
}

void Overlay::Draw() {
    RenderCopyWhole(g_window.rdr, heart.asset->texture, & heart.drect);
    SDL_RenderCopy(g_window.rdr, red_bar.asset->texture, NULL, & red_bar.drect);
    RenderCopyWhole(g_window.rdr, health_bar.asset->texture, & health_bar.drect);
}

void Overlay::Update() {
    red_bar.drect.w = red_bar.asset->frame_width * float(player->current_health) / float(player->max_health);
}