#include "Crosshair.h"

void Crosshair::LoadAsset() {
    texture = LoadAsset_IMG("assets/crosshair.png");
}

void Crosshair::DestroyAsset() {
    SDL_DestroyTexture(texture);
}

void Crosshair::Draw() {
    RenderCopyWhole(g_window.rdr, texture, & render_rect, CENTER);
}

void Crosshair::Update() {
    GetMouseGameState(& render_rect.x, & render_rect.y);
}