#include "Overlay.h"

void Overlay::GivePointers(Player* _player) {
    player = _player;
}

void Overlay::LoadAssets() {

    health_bar_asset = LoadAsset_Ase("assets/health_bar.ase");
    heart_asset = LoadAsset_Ase("assets/heart.ase");

    heart_drect.x = heart_drect.y = 10;

    health_bar_drect.x = heart_drect.x + heart_asset->frame_width + 5;
    health_bar_drect.y = heart_drect.y + heart_asset->frame_height / 2 - health_bar_asset->frame_height / 2;
}

void Overlay::DestroyAssets() {
    DestroyAsset_Ase(heart_asset);
    DestroyAsset_Ase(health_bar_asset);
}

void Overlay::Draw() {
    RenderCopyWhole(g_window.rdr, heart_asset->texture, & heart_drect);
    RenderCopyWhole(g_window.rdr, health_bar_asset->texture, & health_bar_drect);
}

void Overlay::Update() {
}