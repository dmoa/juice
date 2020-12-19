#pragma once

#include <SDL_CP.h>
#include "AssetLoader.h"

struct CurAnimation {
    std::string name;
    int frame_i;
    float tick;
    SDL_Rect quad;
};

inline void _SetAnimation(CurAnimation* anim, Asset_Ase* asset, std::string name) {
    anim->name = name;
    anim->frame_i = asset->tags[name].from;
    anim->tick = asset->frame_durations[anim->frame_i];
    anim->quad = {
                anim->frame_i * asset->frame_height,
                0,
                asset->frame_width,
                asset->frame_height
    };
}

inline void _SetAnimationIf(CurAnimation* anim, Asset_Ase* asset, std::string name) {
    if (name != anim->name) _SetAnimation(anim, asset, name);
}

// @Question for M about inline vs const
inline bool UpdateAnimation(CurAnimation* anim, Asset_Ase* asset, float* dt) {
    anim->tick -= *dt * 1000; // convert dt into milliseconds
    if (anim->tick < 0) {

        Tag_Range t = asset->tags[anim->name];
        anim->frame_i = (anim->frame_i - t.from + 1) % (t.to - t.from + 1) + t.from;
        anim->tick = asset->frame_durations[anim->frame_i];

        anim->quad.x = anim->frame_i * asset->frame_width;

        // Return true if an animation cycle has finished
        if (anim->frame_i - t.from == 0) return true;
    }

    return false;
}