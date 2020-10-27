#include "Player.h"
#include "Map.h"
#include "Enemies.h"
#include "ECS/ECS.h"

void Player::LoadTexture() {
    texture = LoadImage(global_window_data.rdr, "assets/player/red.png");
    is_flipped = SDL_FLIP_HORIZONTAL;
}

void Player::DestroyTexture() {
    SDL_DestroyTexture(texture);
}

void Player::GiveMapEnemiesECSDelta(Map* _map, Enemies* _enemies, ECS* _ecs, float* _dt) {
    map = _map;
    map_cb = map->GetCollisionBoxes();
    enemies = _enemies;
    ecs = _ecs;
    dt = _dt;
}

void Player::InitPos() {
    id = ecs->AddEntity(x, y, PLAYER, PLAYER_TYPE);
}

void Player::Draw() {
    UpdateAnimationQuad(PLAYER, & curr_anim, & spritesheet_quad.x, & spritesheet_quad.y);
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

    if (CTS::Action1() && ! holding_action_button && ! is_attacking) {
        Attack();
    }
    holding_action_button = CTS::Action1();


    // ensures player doesn't go faster when moving diagonally
    if (current_xv && current_yv) {
        current_xv /= ROOT2;
        current_yv /= ROOT2;
    }


    if (cooldown_tick > 0) cooldown_tick -= *dt;
    // player is slower when attacking
    if (is_attacking) {
        current_xv *= 0.4;
        current_yv *= 0.4;
    }

    old_x = x;
    old_y = y;
    x += current_xv * (*dt);
    y += current_yv * (*dt);

    CollisionUpdate();
    rendering_quad = {x, y, 24, 18};
    AnimationUpdate();

    // updating pos in the draw objects, so that it can calculate the draw order.
    ecs->entities[id].x = x;
    ecs->entities[id].y = y;
}

void Player::CollisionUpdate() {

    bool collided_x = false;
    bool collided_y = false;

    for (unsigned int i = 0; i < map_cb->size(); i++) {
        if (AABB(x + COLLISION_DATA[PLAYER].x, y + COLLISION_DATA[PLAYER].y, COLLISION_DATA[PLAYER].w, COLLISION_DATA[PLAYER].h, (*map_cb)[i].x, (*map_cb)[i].y, (*map_cb)[i].w, (*map_cb)[i].h)) {
            if (old_y + COLLISION_DATA[PLAYER].y >= (*map_cb)[i].y + (*map_cb)[i].h) {
                y = (*map_cb)[i].y + (*map_cb)[i].h - COLLISION_DATA[PLAYER].y;
                collided_y = true;
            }
            if (old_x + COLLISION_DATA[PLAYER].x >= (*map_cb)[i].x + (*map_cb)[i].w) {
                x = (*map_cb)[i].x + (*map_cb)[i].w - COLLISION_DATA[PLAYER].x;
                collided_x = true;
            }
            if (old_y + COLLISION_DATA[PLAYER].y + COLLISION_DATA[PLAYER].h <= (*map_cb)[i].y) {
                y = (*map_cb)[i].y - COLLISION_DATA[PLAYER].y - COLLISION_DATA[PLAYER].h;
                collided_y = true;
            }
            if (old_x + COLLISION_DATA[PLAYER].x + COLLISION_DATA[PLAYER].w <= (*map_cb)[i].x) {
                x = (*map_cb)[i].x - COLLISION_DATA[PLAYER].x - COLLISION_DATA[PLAYER].w;
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

    bool finished_anim = AnimationTick(PLAYER, & curr_anim, dt);

    is_attacking = is_attacking && ! finished_anim;

    if (! is_attacking) {
        if (current_xv || current_yv) {
            SetAnimationIf(PLAYER, & curr_anim, RUN);
        }
        else {
            SetAnimationIf(PLAYER, & curr_anim, IDLE);
        }
    }

}

void Player::Attack() {
    is_attacking = true;

    for (auto it = enemies->enemies.begin(); it != enemies->enemies.end();) {

        // we save the current iterator, as PopEntity deletes items in enemies->enemies.
        // If we were to do i++ at the end of the loop, then i++ would freak out and crash
        // because it doesn't know how to find the next item as the item it's currently pointing
        // to just got deleted. We fix this by doing it++ previously, so that it can find the next
        // item in advance.

        auto current = it++;
        Entity e = ecs->entities[current->first];

        if (Entities_AABB(e.name, e.x, e.y, PLAYER, x, y)) {
            ecs->PopEntity(current->first);
        }
    }

    cooldown_tick = cooldown;
    SetAnimation(PLAYER, & curr_anim, ATTACK);
}