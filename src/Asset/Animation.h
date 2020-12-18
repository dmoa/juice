#pragma once

#include <SDL_CP.h>
#include "AssetLoader.h"

// inline bool AnimationTick(ENTITY_NAME e_name, CurrAnimation* anim, float* dt) {
//     if (anim->type == ANIM_NONE) return false;

//     anim->tick -= (*dt);


//     if (anim->tick < 0) {
//         anim->tick = ANIMATION_DATA[e_name][anim->type].speed;
//         anim->frame = (anim->frame + 1) % ANIMATION_DATA[e_name][anim->type].num_frames;
//     }

//     // return true if the animation has finished (or started again).
//     if (anim->frame == 0) return true;

//     return false;
// }

// inline void SetAnimation(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type) {
//     anim->type = new_type;
//     anim->tick = ANIMATION_DATA[e_name][new_type].speed;
//     anim->frame = 1;
// }

// inline void SetAnimationIf(ENTITY_NAME e_name, CurrAnimation* anim, ANIMATION_TYPE new_type) {
//     if (anim->type != new_type) SetAnimation(e_name, anim, new_type);
// }

// inline void UpdateAnimationQuad(ENTITY_NAME e_name, CurrAnimation* anim, SDL_Rect* quad) {
//     *quad = {
//         QUAD_DIMENSIONS[e_name].w * anim->frame,
//         QUAD_DIMENSIONS[e_name].h * ANIMATION_DATA[e_name][anim->type].spreadsheet_index_y,
//         QUAD_DIMENSIONS[e_name].w,
//         QUAD_DIMENSIONS[e_name].h
//     };
// }

struct CurAnimation {
    std::string name;
    int frame_i;
    float tick;
    SDL_Rect quad;
};

inline void _SetAnimation(CurAnimation* anim, Asset_Ase* asset, std::string name) {
    anim->name    = name;
    anim->frame_i = asset->tags[name].from;
    anim->tick    = asset->frame_durations[anim->frame_i];
    anim->quad    = {
                    anim->frame_i * asset->frame_height,
                    0,
                    asset->frame_width,
                    asset->frame_height
    };
}

inline void _SetAnimationIf(CurAnimation* anim, Asset_Ase* asset, std::string name) {
    if (name != anim->name) _SetAnimation(anim, asset, name);
}

// @Question for M
inline bool UpdateAnimation(CurAnimation* anim, Asset_Ase* asset, float* dt) {
    anim->tick -= *dt * 1000; // convert dt into milliseconds
    if (anim->tick < 0) {

        Tag_Range t = asset->tags[anim->name];
        anim->frame_i = (anim->frame_i + 1) % (t.to - t.from + 1) + t.from;
        anim->tick = asset->frame_durations[anim->frame_i];

        anim->quad.x = anim->frame_i * asset->frame_width;

        return true;
    }
    return false;
}