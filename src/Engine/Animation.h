#pragma once

#include <Engine/Engine.h>
#include "Asset.h"

struct CurAnimation {
    std::string name;
    int frame_i;
    float tick;
    SDL_Rect quad;
};

inline Tag_Range GetTag(Tags tags, const char* str) {
    for (u16 i = 0; i < tags.num_tags; i++) {
        if (strequal(tags.tags[i].name, str)) return tags.tags[i];
    }
    return {"", -1, -1};
}

inline void SetAnimation(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name) {

    Tag_Range tag = GetTag(asset->tags, name.c_str());

    // If animation doesn't exist, don't bother.
    // We can check if from is -1, because that is what returned from GetTag if we can't find the animation.
    if (tag.from == -1) {
        printf("Failed to set animation %s for asset %s\n", name.c_str(), asset->file_path.str);
        return;
    }

    anim->name = name;
    anim->frame_i = tag.from;
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

        Tag_Range t = GetTag(asset->tags, anim->name.c_str());
        anim->frame_i = (anim->frame_i - t.from + 1) % (t.to - t.from + 1) + t.from;
        anim->tick = asset->frame_durations[anim->frame_i];

        anim->quad.x = anim->frame_i * asset->frame_width;

        // Return true if an animation cycle has finished
        if (anim->frame_i - t.from == 0) return true;
    }

    return false;
}