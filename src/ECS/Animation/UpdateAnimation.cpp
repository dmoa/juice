#include "UpdateAnimation.hpp"

bool AnimationTick(float* dt, std::string* curr_anim, float* tick, int* curr_frame, ENTITY_NAME name) {
    *tick -= (*dt);

    int animation_type_index = ENTITY_ANIMATION_DATA[name].animation_types[*curr_anim];

    if (*tick < 0) {
        *tick = ENTITY_ANIMATION_DATA[name].speeds[animation_type_index];
        *curr_frame = (*curr_frame + 1) % ENTITY_ANIMATION_DATA[name].num_frames[animation_type_index];
    }

    // return true if the animation has finished (restarted).
    if (*curr_frame == 0) return true;

    return false;
}

void SetAnimation(std::string* curr_anim, std::string new_anim, float* tick, int* curr_frame, ENTITY_NAME name) {
    *curr_anim = new_anim;

    int animation_type_index = ENTITY_ANIMATION_DATA[name].animation_types[*curr_anim];

    *tick = ENTITY_ANIMATION_DATA[name].speeds[animation_type_index];
    *curr_frame = 1;
}

void SetAnimationIf(std::string* curr_anim, std::string new_anim, float* tick, int* curr_frame, ENTITY_NAME name) {
    if (*curr_anim != new_anim) SetAnimation(curr_anim, new_anim, tick, curr_frame, name);
}

void UpdateAnimationQuad(std::string curr_anim, int curr_frame, ENTITY_NAME name, int* x, int* y) {
    int animation_type_index = ENTITY_ANIMATION_DATA[name].animation_types[curr_anim];

    *x = ENTITY_QUAD_DIMENSIONS.ws[name] * curr_frame;
    *y = ENTITY_QUAD_DIMENSIONS.hs[name] * animation_type_index;
}