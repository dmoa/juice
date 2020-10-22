#include "UpdateAnimation.hpp"

bool AnimationTick(ENTITY_NAME e_name, CurrAnimation* anim, float* dt) {

    anim->tick -= (*dt);

        *curr_frame = (*curr_frame + 1) % ENTITY_ANIMATION_DATA[name].num_frames[animation_type_index];

    if (anim->tick < 0) {
        anim->tick = ANIMATION_DATA[e_name][anim->type].speed;
        anim->frame = (anim->frame + 1) % ANIMATION_DATA[e_name][anim->type].num_frames;
    }

    // return true if the animation has finished (or started again).
    if (anim->frame == 0) return true;

    return false;
}

void SetAnimation(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type) {
    anim->type = new_type;
    anim->tick = ANIMATION_DATA[e_name][new_type].speed;
    anim->frame = 1;
}

void SetAnimationIf(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type) {
    if (anim->type != new_type) SetAnimation(e_name, anim, new_type);
}

void UpdateAnimationQuad(ENTITY_NAME e_name, CurrAnimation* anim, int* x, int* y) {
    *x = ENTITY_QUAD_DIMENSIONS[e_name].w * anim->frame;
    *y = ENTITY_QUAD_DIMENSIONS[e_name].h * ANIMATION_DATA[e_name][anim->type].spreadsheet_index_y;
}