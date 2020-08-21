#include "Camera.hpp"

void Camera::GivePlayerMapDelta(Player* _player, Map* _map, float* _dt) {
    player = _player;
    map = _map;
    dt = _dt;
}

SDL_Rect* Camera::GetViewport() {
    return & viewport;
}

void Camera::Update() {
    real_x = player->GetCenterX() - global_window_data.w / global_window_data.scale / 2;
    real_y = player->GetCenterY() - global_window_data.h / global_window_data.scale / 2;

    if (real_x < 0) real_x = 0;
    if (real_y < 0) real_y = 0;
    if (real_x + global_window_data.w / global_window_data.scale > map->GetMapWidth()) {
        real_x = map->GetMapWidth() - global_window_data.w / global_window_data.scale;
    }
    if (real_y + global_window_data.h / global_window_data.scale > map->GetMapHeight()) {
        real_y = map->GetMapWidth() - global_window_data.h / global_window_data.scale;
    }

    viewport = {real_x, real_y, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
}

void Camera::DevUpdate() {
    if (global_window_data.keys_down[SDL_SCANCODE_D]) {
        real_x += pan_v * (*dt);
    }
    if (global_window_data.keys_down[SDL_SCANCODE_A]) {
        real_x -= pan_v * (*dt);
    }
    if (global_window_data.keys_down[SDL_SCANCODE_S]) {
        real_y += pan_v * (*dt);
    }
    if (global_window_data.keys_down[SDL_SCANCODE_W]) {
        real_y -= pan_v * (*dt);
    }
    viewport = {real_x, real_y, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
}