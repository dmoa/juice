#include "Player.hpp"

void Player::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/player/red.png");
    if (!texture) SDL_Log("red.png not found");
    is_flipped = SDL_FLIP_HORIZONTAL;
}

void Player::Draw() {
    SDL_RenderCopyEx(global_window_data.rdr, texture, & current_spritesheet_quad, & rendering_quad, NULL, NULL, is_flipped);
}

void Player::Update() {

    current_xv = 0;
    current_yv = 0;
    if (!((global_window_data.keys_down[SDL_SCANCODE_RIGHT] || global_window_data.keys_down[SDL_SCANCODE_D]) && (global_window_data.keys_down[SDL_SCANCODE_LEFT] || global_window_data.keys_down[SDL_SCANCODE_A]))) {
        if (global_window_data.keys_down[SDL_SCANCODE_RIGHT] || global_window_data.keys_down[SDL_SCANCODE_D]) {
            current_xv = v;
            is_flipped = SDL_FLIP_NONE;

        }
        if (global_window_data.keys_down[SDL_SCANCODE_LEFT] || global_window_data.keys_down[SDL_SCANCODE_A]) {
            current_xv = -v;
            is_flipped = SDL_FLIP_HORIZONTAL;

        }
    }
    if (!((global_window_data.keys_down[SDL_SCANCODE_UP] || global_window_data.keys_down[SDL_SCANCODE_W]) && (global_window_data.keys_down[SDL_SCANCODE_DOWN] || global_window_data.keys_down[SDL_SCANCODE_S]))) {
        if (global_window_data.keys_down[SDL_SCANCODE_UP] || global_window_data.keys_down[SDL_SCANCODE_W]) {
            current_yv = -v;
        }
        if (global_window_data.keys_down[SDL_SCANCODE_DOWN] || global_window_data.keys_down[SDL_SCANCODE_S]) {
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
}

void Player::CollisionUpdate() {

    bool collided_x = false;
    bool collided_y = false;

    for (unsigned int i = 0; i < map_cb->ws.size(); i++) {
        if (AABB(x + extra_collision_info.offset_x, y + extra_collision_info.offset_y, extra_collision_info.w, extra_collision_info.h, map_cb->xs[i], map_cb->ys[i], map_cb->ws[i], map_cb->hs[i])) {
            if (old_y + extra_collision_info.offset_y >= map_cb->ys[i] + map_cb->hs[i]) {
                y = map_cb->ys[i] + map_cb->hs[i] - extra_collision_info.offset_y;
                collided_y = true;
            }
            if (old_x + extra_collision_info.offset_x >= map_cb->xs[i] + map_cb->ws[i]) {
                x = map_cb->xs[i] + map_cb->ws[i] - extra_collision_info.offset_x;
                collided_x = true;
            }
            if (old_y + extra_collision_info.offset_y + extra_collision_info.h <= map_cb->ys[i]) {
                y = map_cb->ys[i] - extra_collision_info.offset_y - extra_collision_info.h;
                collided_y = true;
            }
            if (old_x + extra_collision_info.offset_x + extra_collision_info.w <= map_cb->xs[i]) {
                y = map_cb->xs[i] - extra_collision_info.offset_x - extra_collision_info.w;
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
        }
        if (collided_x) {
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