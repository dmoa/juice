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

    int proposed_x = player->GetCenterX() - global_window_data.w / global_window_data.scale / 2;
    int proposed_y = player->GetCenterY() - global_window_data.h / global_window_data.scale / 2;

    if (proposed_x - real_x >   max_distance_from_player) real_x = proposed_x - max_distance_from_player;
    if (proposed_x - real_x < - max_distance_from_player) real_x = proposed_x + max_distance_from_player;
    if (proposed_y - real_y >   max_distance_from_player) real_y = proposed_y - max_distance_from_player;
    if (proposed_y - real_y < - max_distance_from_player) real_y = proposed_y + max_distance_from_player;

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
    if (CTS::Right()) {
        real_x += pan_v * (*dt);
    }
    if (CTS::Left()) {
        real_x -= pan_v * (*dt);
    }
    if (CTS::Down()) {
        real_y += pan_v * (*dt);
    }
    if (CTS::Up()) {
        real_y -= pan_v * (*dt);
    }
    viewport = {real_x, real_y, global_window_data.w / global_window_data.scale, global_window_data.h / global_window_data.scale};
}