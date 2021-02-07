#pragma once

#include <Engine/Engine.h>
#include "Asset.h"

struct CurAnimation {
    std::string name;
    int frame_i;
    float tick;
    SDL_Rect quad;
};

inline void SetAnimation(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name) {

    asset->tags.find("Idle");

    // If animation doesn't exist, don't bother.
    if (asset->tags.find(name) == asset->tags.end()) {
        SDL_Log("Failed to set animation %s for asset %s\n", name.c_str(), asset->file_path.c_str());
        return;
    }

    anim->name = name;
    anim->frame_i = asset->tags[name].from;
    anim->tick = asset->frame_durations[anim->frame_i];
    anim->quad = {
                anim->frame_i * asset->frame_width,
                0,
                asset->frame_width,
                asset->frame_height
    };
}

inline void SetAnimationIf(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name) {
    if (name != anim->name) SetAnimation(anim, asset, name);
}

inline bool UpdateAnimation(CurAnimation* anim, Asset_Ase_Animated* asset) {
    anim->tick -= g_dt * 1000; // convert dt into milliseconds
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