#include "Player.hpp"

void Player::LoadTexture() {
    texture = IMG_LoadTexture(global_window_data.rdr, "assets/player/red.png");
    if (!texture) SDL_Log("red.png not found");

    current_quad.x = current_quad.y = positional_quad.x = positional_quad.y = 0;
    current_quad.w = current_quad.h = positional_quad.w = positional_quad.h = 24;
    // SDL_QueryTexture(texture, NULL, NULL, & current_quad.w, & current_quad.h); SDL_TEXTUREACCESS_STATIC
    is_flipped = SDL_FLIP_HORIZONTAL;
}

void Player::GiveDT(float* _dt) {
    dt = _dt;
}

void Player::Draw() {
    SDL_RenderCopyEx(global_window_data.rdr, texture, & current_quad, & positional_quad, NULL, NULL, is_flipped);
}

void Player::Update() {
    current_animation.timer -= *dt;
    if (current_animation.timer < 0) {
        current_animation.timer = *current_animation.speed;
        current_animation.index = (current_animation.index + 1) % *current_animation.num_frames + current_animation.offset;

        current_quad.x = current_animation.index * current_quad.w;
    }

    if (!(global_window_data.keys_down[SDL_SCANCODE_LEFT] && global_window_data.keys_down[SDL_SCANCODE_RIGHT]) && (global_window_data.keys_down[SDL_SCANCODE_RIGHT] || global_window_data.keys_down[SDL_SCANCODE_LEFT])) {
        if (global_window_data.keys_down[SDL_SCANCODE_RIGHT]) {
            x += xv * (*dt);
            is_flipped = SDL_FLIP_NONE;
        }
        if (global_window_data.keys_down[SDL_SCANCODE_LEFT]) {
            x -= xv * (*dt);
            is_flipped = SDL_FLIP_HORIZONTAL;
        }
        positional_quad.x = x;
    
        SetAnimationIfShould("running");
    } else {
        SetAnimationIfShould("idle");
    }
}

void Player::SetAnimationIfShould(std::string name) {

    if (name != current_animation.name) {
        current_animation.name = name;

        int index = 0;
        if (current_animation.name == "running") {
            index = 1;
        }
        current_animation.timer = 0;
        current_animation.speed = & animations_data.speeds[index];
        current_animation.num_frames = & animations_data.num_frames[index];

    }
}