#include "Player.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"

void Player::LoadTexture() {
    texture = LoadImage(global_window_data.rdr, "assets/player/red.png");
    is_flipped = SDL_FLIP_HORIZONTAL;
}

void Player::GiveMapDeltaECS(Map* _map, float* _dt, ECS* _ecs) {
    dt = _dt;
    map = _map;
    map_cb = map->GetCollisionBoxes();
    ecs = _ecs;
}

void Player::InitPos() {
    id = ecs->AddEntity(x, y, PLAYER, PLAYER_TYPE);
}

void Player::Draw() {
    SDL_RenderCopyEx(global_window_data.rdr, texture, & current_spritesheet_quad, & rendering_quad, NULL, NULL, is_flipped);
}

void Player::Update() {

    current_xv = 0;
    current_yv = 0;
    if (!(CTS::Left() && CTS::Right())) {
        if (CTS::Right()) {
            current_xv = v;
            is_flipped = SDL_FLIP_NONE;

        }
        if (CTS::Left()) {
            current_xv = -v;
            is_flipped = SDL_FLIP_HORIZONTAL;

        }
    }
    if (!(CTS::Up() && CTS::Down())) {
        if (CTS::Up()) {
            current_yv = -v;
        }
        if (CTS::Down()) {
            current_yv = v;
        }
    }

    if (current_xv && current_yv) { // ensures player doesn't go faster when moving diagonally
        current_xv /= ROOT2;
        current_yv /= ROOT2;
    }

    old_x = x;
    old_y = y;
    x += current_xv * (*dt);
    y += current_yv * (*dt);

    CollisionUpdate();
    rendering_quad = {x, y, 24, 18};
    AnimationUpdate();

    // updating pos in the draw objects, so that it can calculate the draw order.
    ecs->entities.xs[id] = x;
    ecs->entities.ys[id] = y;
}

void Player::CollisionUpdate() {

    bool collided_x = false;
    bool collided_y = false;

    for (unsigned int i = 0; i < map_cb->ws.size(); i++) {
        if (AABB(x + collision_info.offset_x, y + collision_info.offset_y, collision_info.w, collision_info.h, map_cb->xs[i], map_cb->ys[i], map_cb->ws[i], map_cb->hs[i])) {
            if (old_y + collision_info.offset_y >= map_cb->ys[i] + map_cb->hs[i]) {
                y = map_cb->ys[i] + map_cb->hs[i] - collision_info.offset_y;
                collided_y = true;
            }
            if (old_x + collision_info.offset_x >= map_cb->xs[i] + map_cb->ws[i]) {
                x = map_cb->xs[i] + map_cb->ws[i] - collision_info.offset_x;
                collided_x = true;
            }
            if (old_y + collision_info.offset_y + collision_info.h <= map_cb->ys[i]) {
                y = map_cb->ys[i] - collision_info.offset_y - collision_info.h;
                collided_y = true;
            }
            if (old_x + collision_info.offset_x + collision_info.w <= map_cb->xs[i]) {
                x = map_cb->xs[i] - collision_info.offset_x - collision_info.w;
                collided_x = true;
            }
        }
    }

    // If the player was trying to go diagonally, but could only go on one axis,
    // further his position on that axis, because when you hold down both keys, the xv and yv are reduced
    // so you go at the same speed diagonally. But because the player wasn't able to go diagonally, we remove
    // the reduced xv from the position and add the true xv.
    if (current_xv && current_yv) {
        if (collided_y) {
            x += ((current_xv > 0 ? v : - v) - current_xv) * (*dt);
            current_yv = 0;
            CollisionUpdate();
        } else if (collided_x) {
            y += ((current_yv > 0 ? v: - v) - current_yv) * (*dt);
            current_xv = 0;
            CollisionUpdate();
        }
    }
}

void Player::AnimationUpdate() {
    current_animation.timer -= *dt;
    if (current_animation.timer < 0) {

        current_animation.timer = current_animation.speed;
        current_animation.index = (current_animation.index + 1) % current_animation.num_frames;

        current_spritesheet_quad.x = (current_animation.index + current_animation.offset) * current_spritesheet_quad.w;
    }

    if (current_xv || current_yv) SetAnimationIfShould("running");
    else                          SetAnimationIfShould("idle");
}

void Player::SetAnimationIfShould(std::string name) {

    if (name != current_animation.name) {
        current_animation.name = name;
        int index = animations_data.names[name];

        current_animation.timer = 0;
        current_animation.speed      = animations_data.speeds[index];
        current_animation.num_frames = animations_data.num_frames[index];
        current_animation.offset     = animations_data.offsets[index];

    }
}

void Player::DestroyTexture() {
    SDL_DestroyTexture(texture);
}