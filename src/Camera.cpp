#include "Camera.h"

void Camera::PassPointers(Player* _player, Map* _map, float* _dt) {
    player = _player;
    map = _map;
    dt = _dt;
}

void Camera::Update() {

    int proposed_x = player->GetDrawCenterX() - g_window.w / g_window.scale / 2;
    int proposed_y = player->GetDrawCenterY() - g_window.h / g_window.scale / 2;

    if (proposed_x - real_x >   max_distance_from_player) real_x = proposed_x - max_distance_from_player;
    if (proposed_x - real_x < - max_distance_from_player) real_x = proposed_x + max_distance_from_player;
    if (proposed_y - real_y >   max_distance_from_player) real_y = proposed_y - max_distance_from_player;
    if (proposed_y - real_y < - max_distance_from_player) real_y = proposed_y + max_distance_from_player;

    if (real_x < 0) real_x = 0;
    if (real_y < 0) real_y = 0;
    if (real_x + g_window.w / g_window.scale > map->GetMapWidth()) {
        real_x = map->GetMapWidth() - g_window.w / g_window.scale;
    }
    if (real_y + g_window.h / g_window.scale > map->GetMapHeight()) {
        real_y = map->GetMapWidth() - g_window.h / g_window.scale;
    }

    g_window.gameplay_viewport = {real_x, real_y, g_window.w / g_window.scale, g_window.h / g_window.scale};
}

void Camera::DevUpdate() {
    if (g_controls.Right()) {
        real_x += pan_v * (g_dt);
    }
    if (g_controls.Left()) {
        real_x -= pan_v * (g_dt);
    }
    if (g_controls.Down()) {
        real_y += pan_v * (g_dt);
    }
    if (g_controls.Up()) {
        real_y -= pan_v * (g_dt);
    }
    g_window.gameplay_viewport = {real_x, real_y, g_window.w / g_window.scale, g_window.h / g_window.scale};
}