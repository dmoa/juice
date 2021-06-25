#include "Player.h"
#include "Map.h"
#include "Enemies.h"
#include "ECS/ECS.h"

void Player::LoadAsset() {

    // See header for explanation
    _asset = LoadAsset_Ase_Animated("assets/player/knight.ase");
    asset = (Asset_Ase**) (& _asset);

    weapon.asset = LoadAsset_Ase("assets/player/weapons/knife.ase");

    is_flipped = SDL_FLIP_HORIZONTAL;
    Animation_Set(& cur_anim, _asset, "Idle");

    rendering_quad.w = cur_anim.quad.w;
    rendering_quad.h = cur_anim.quad.h;
}

void Player::DestroyAsset() {
    DestroyAsset_Ase_Animated(_asset);
    DestroyAsset_Ase(weapon.asset);
}

void Player::PassPointers(Map* _map, Enemies* _enemies, ECS* _ecs, Crosshair* _crosshair) {
    map = _map;
    map_cb = _map->GetCollisionBoxes();
    enemies = _enemies;
    ecs = _ecs;
    crosshair = _crosshair;
}

void Player::InitPos() {
    x = y = 40;
    type = PLAYER_TYPE;
    ecs->AddEntity( (Entity*) this );
}

void Player::Draw() {

    // If the angle of the weapon makes the weapon point towards the top, then draw the weapon behind the player.
    if (weapon.angle < 90 || weapon.angle > 270) {
        DrawWeapon();
        DrawCharacter();
    }
    else {
        DrawCharacter();
        DrawWeapon();
    }
}

void Player::DrawCharacter() {
    SDL_RenderCopyEx(g_window.rdr, _asset->texture, & cur_anim.quad, & rendering_quad, NULL, NULL, is_flipped);
}

void Player::DrawWeapon() {

    weapon.pivot = {weapon.asset->frame_width / 2, weapon.asset->frame_height};
    // drect's y is + .5 * frame_height to align center of weapon with player center. Pivot.y is to offset the rotation since SDL pivots relative to drect.
    // We offset to make sure it pivots around the player center.
    weapon.drect = {GetDrawCenterX() - weapon.asset->frame_width / 2, GetDrawCenterY() - weapon.pivot.y, weapon.asset->frame_width, weapon.asset->frame_height};
    SDL_RenderCopyEx(g_window.rdr, weapon.asset->texture, NULL, & weapon.drect, weapon.angle, & weapon.pivot, weapon.is_flipped);
}

void Player::Update() {
    UpdateMovement();
    UpdateCollision();
    rendering_quad.x = x;
    rendering_quad.y = y;
    UpdateAnimation();
    UpdateWeapon();
}

void Player::UpdateMovement() {

    current_xv = 0;
    current_yv = 0;

    float joystick_xm = ControllerAxis(JOYSTICK_LEFTX);
    float joystick_ym = ControllerAxis(JOYSTICK_LEFTY);
    float joystick_m = pyth(joystick_xm, joystick_ym);

    // If joystick is used, then calculate movement from the joystick data.
    // Otherwise, read keyboard input.
    if (joystick_m > AXIS_MIN_MOVED) {
        float sf = v / joystick_m * (joystick_m / AXIS_MAX);

        current_xv = joystick_xm * sf;
        current_yv = joystick_ym * sf;
    }
    else {
        if (g_controls.Right() && ! g_controls.Left()) {
            current_xv = v;
        }
        if (g_controls.Left() && ! g_controls.Right()) {
            current_xv = -v;
        }
        if (g_controls.Up() && ! g_controls.Down()) {
            current_yv = -v;
        }
        if (g_controls.Down() && ! g_controls.Up()) {
            current_yv = v;
        }

        // ensures player doesn't go faster when moving diagonally
        if (current_xv && current_yv) {
            current_xv /= ROOT2;
            current_yv /= ROOT2;
        }
    }

    if (g_controls.Action1() && ! holding_action_button && weapon.attack_tick < - weapon.attack_break) {
        Attack();
    }
    holding_action_button = g_controls.Action1();

    // player is slower when attacking
    if (is_attacking) {
        current_xv *= 0.4;
        current_yv *= 0.4;
    }

    old_x = x;
    old_y = y;
    x += current_xv * (g_dt);
    y += current_yv * (g_dt);
}

void Player::UpdateCollision() {

    bool collided_x = false;
    bool collided_y = false;

    for (unsigned int i = 0; i < map_cb->size(); i++) {
        if (AABB(x + (*asset)->movement_box->x, y + (*asset)->movement_box->y, (*asset)->movement_box->w, (*asset)->movement_box->h, (*map_cb)[i].x, (*map_cb)[i].y, (*map_cb)[i].w, (*map_cb)[i].h)) {
            if (old_y + (*asset)->movement_box->y >= (*map_cb)[i].y + (*map_cb)[i].h) {
                y = (*map_cb)[i].y + (*map_cb)[i].h - (*asset)->movement_box->y;
                collided_y = true;
            }
            if (old_x + (*asset)->movement_box->x >= (*map_cb)[i].x + (*map_cb)[i].w) {
                x = (*map_cb)[i].x + (*map_cb)[i].w - (*asset)->movement_box->x;
                collided_x = true;
            }
            if (old_y + (*asset)->movement_box->y + (*asset)->movement_box->h <= (*map_cb)[i].y) {
                y = (*map_cb)[i].y - (*asset)->movement_box->y - (*asset)->movement_box->h;
                collided_y = true;
            }
            if (old_x + (*asset)->movement_box->x + (*asset)->movement_box->w <= (*map_cb)[i].x) {
                x = (*map_cb)[i].x - (*asset)->movement_box->x - (*asset)->movement_box->w;
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
            x += ((current_xv > 0 ? v : - v) - current_xv) * (g_dt);
            current_yv = 0;
            UpdateCollision();
        }
        else if (collided_x) {
            y += ((current_yv > 0 ? v: - v) - current_yv) * (g_dt);
            current_xv = 0;
            UpdateCollision();
        }
    }
}

void Player::UpdateAnimation() {

    bool finished_anim = Animation_Update(& cur_anim, _asset);

    if (! is_attacking) {
        if (current_xv || current_yv) {
            Animation_SetIf(& cur_anim, _asset, "Run");
        }
        else {
            Animation_SetIf(& cur_anim, _asset, "Idle");
        }
    }

    // Only change direction if crosshair is actually drawn / active.
    if (crosshair->is_drawn) {
        // Player direction depends whether the crosshair is to the left or to the right of the center of the player.
        if (crosshair->x > GetDrawCenterX()) {
            is_flipped = SDL_FLIP_NONE;
        }
        else {
            is_flipped = SDL_FLIP_HORIZONTAL;
        }
    }

}

void Player::UpdateWeapon() {

    int mouse_x; int mouse_y;
    GetMouseGameState(& mouse_x, & mouse_y);

    // If not attacking, weapon should follow mouse. Otherwise do weapon swing.
    if (! is_attacking) {

        // Update the angle only if the crosshair is on the screen, otherwise, assume crosshair position relative to player has not changed.
        if (crosshair->is_drawn) {
            // +90 at the end because atan2's range is (-rad,rad), when we want (0,360), not (-180, 180).
            // +180 to make the weapon face away from the cursor.
            weapon.angle = atan2(crosshair->y - GetDrawCenterY(), crosshair->x - GetDrawCenterX()) * 180 / PI + 270;
        }

    }
    else {
        weapon.angle += weapon.swing_angle / weapon.attack_length * (g_dt);

        if (weapon.attack_tick < 0) {
            is_attacking = false;
            weapon.is_flipped = (SDL_RendererFlip) ! weapon.is_flipped;
        }
    }

    // We want this to continually tick so that we can use it to check whether attack_break time has passed.
    // i.e. if weapon.attack_tick < - weapon.attack_break, then we know that the min time between the weapon attacks has passed.
    weapon.attack_tick -= g_dt;

}

void Player::Attack() {

    is_attacking = true;
    weapon.attack_tick = weapon.attack_length;

    // Haven't decided whether clockwise / anticlockwise will be alternating or be random.

    // Randomising whether sword will swing clockwise or anticlockwise
    //int rand = random(0, 2);
    //if (rand) weapon.swing_angle *= -1;
    weapon.swing_angle *= -1;
}

void Player::FinishUpdate() {

    if (is_attacking) {
        for (int i = 0; i < MAX_ENEMIES; i++) {
            Barrel* b = & enemies->barrels[i];

            // Clipping and transforming the draw rectangle of weapon with the bounds damage box rectangle of weapon.
            SDL_Rect _damage_box = weapon.drect;
            _damage_box.x += weapon.asset->damage_box->x;
            _damage_box.y += weapon.asset->damage_box->y;
            _damage_box.w = weapon.asset->damage_box->w;
            _damage_box.h = weapon.asset->damage_box->h;

            v2 player_damage_box [4];
            RectToV2(& _damage_box, player_damage_box);

            // Clipping and transforming the draw rectangle of enemy with the bounds movement rectangle (we assume the movement rectangle is where the enemy can be damaged).

            SDL_Rect enemy_can_be_damage_box = {
                b->x + (*b->asset)->movement_box->x,
                b->y + (*b->asset)->movement_box->y,
                (*b->asset)->movement_box->w,
                (*b->asset)->movement_box->h
            };

            if (PolygonRectangle(player_damage_box, & enemy_can_be_damage_box)) {
                b->should_delete = true;
            }
        }
    }

}