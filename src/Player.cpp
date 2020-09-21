#include "Player.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"

void Player::LoadTexture() {
    texture = LoadImage(global_window_data.rdr, "assets/player/red.png");
    is_flipped = SDL_FLIP_HORIZONTAL;
}

void Player::DestroyTexture() {
    SDL_DestroyTexture(texture);
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
    UpdateAnimationQuad(curr_animation, curr_animation_frame, PLAYER, & spritesheet_quad.x, & spritesheet_quad.y);
    SDL_RenderCopyEx(global_window_data.rdr, texture, & spritesheet_quad, & rendering_quad, NULL, NULL, is_flipped);
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
        if (AABB(x + ENTITY_COLLISION_DATA.xs[PLAYER], y + ENTITY_COLLISION_DATA.ys[PLAYER], ENTITY_COLLISION_DATA.ws[PLAYER], ENTITY_COLLISION_DATA.hs[PLAYER], map_cb->xs[i], map_cb->ys[i], map_cb->ws[i], map_cb->hs[i])) {
            if (old_y + ENTITY_COLLISION_DATA.ys[PLAYER] >= map_cb->ys[i] + map_cb->hs[i]) {
                y = map_cb->ys[i] + map_cb->hs[i] - ENTITY_COLLISION_DATA.ys[PLAYER];
                collided_y = true;
            }
            if (old_x + ENTITY_COLLISION_DATA.xs[PLAYER] >= map_cb->xs[i] + map_cb->ws[i]) {
                x = map_cb->xs[i] + map_cb->ws[i] - ENTITY_COLLISION_DATA.xs[PLAYER];
                collided_x = true;
            }
            if (old_y + ENTITY_COLLISION_DATA.ys[PLAYER] + ENTITY_COLLISION_DATA.hs[PLAYER] <= map_cb->ys[i]) {
                y = map_cb->ys[i] - ENTITY_COLLISION_DATA.ys[PLAYER] - ENTITY_COLLISION_DATA.hs[PLAYER];
                collided_y = true;
            }
            if (old_x + ENTITY_COLLISION_DATA.xs[PLAYER] + ENTITY_COLLISION_DATA.ws[PLAYER] <= map_cb->xs[i]) {
                x = map_cb->xs[i] - ENTITY_COLLISION_DATA.xs[PLAYER] - ENTITY_COLLISION_DATA.ws[PLAYER];
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

    bool finished_anim = AnimationTick(dt, & curr_animation, & animation_tick, & curr_animation_frame, PLAYER);

    if (! is_attacking || (is_attacking && finished_anim)) {
        if (current_xv || current_yv) {
            if (curr_animation != "running") SetAnimation(& curr_animation, "running", & animation_tick, & curr_animation_frame, PLAYER);
        }
        else if (curr_animation != "idle") {
            SetAnimation(& curr_animation, "idle", & animation_tick, & curr_animation_frame, PLAYER);
        }
    }

}

void Player::Attack() {
    is_attacking = true;
    if (curr_animation != "attack") {
        SetAnimation(& curr_animation, "attack", & animation_tick, & curr_animation_frame, PLAYER);
    }
}


// @TODO
// set is_attacking to false when the animation stops being attack.