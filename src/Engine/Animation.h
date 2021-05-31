#pragma once

#include <Engine/Engine.h>
#include "Asset.h"

struct CurAnimation {
    char* name = NULL;
    int frame_i;
    float tick;
    SDL_Rect quad;
};

inline Tag_Range GetTag(Tags tags, char* str) {
    for (u16 i = 0; i < tags.num_tags; i++) {
        if (strequal(tags.tags[i].name, str)) return tags.tags[i];
    }
    return {"", -1, -1};
}

inline void Animation_Set(CurAnimation* anim, Asset_Ase_Animated* asset, char* name) {

    Tag_Range tag = GetTag(asset->tags, name);

    // If animation doesn't exist, don't bother.
    // We can check if from is -1, because that is what returned from GetTag if we can't find the animation.
    if (tag.from == -1) {
        printf("Failed to set animation %s for asset %s\n", name, asset->file_path);
        return;
    }

    free(anim->name); // Free will ignore if anim->name is NULL, so nothing to worry about.
    anim->name = strmalloc(name);

    anim->frame_i = tag.from;
    anim->tick = asset->frame_durations[anim->frame_i];
    anim->quad = {
                 anim->frame_i * asset->frame_width,
                 0,
                 asset->frame_width,
                 asset->frame_height
    };
}

inline void Animation_SetIf(CurAnimation* anim, Asset_Ase_Animated* asset, char* name) {
    if (! strequal(name, anim->name)) Animation_Set(anim, asset, name);
}

inline bool Animation_Update(CurAnimation* anim, Asset_Ase_Animated* asset) {
    anim->tick -= g_dt * 1000; // convert dt into milliseconds
    if (anim->tick < 0) {

        Tag_Range t = GetTag(asset->tags, anim->name);
        anim->frame_i = (anim->frame_i - t.from + 1) % (t.to - t.from + 1) + t.from;
        anim->tick = asset->frame_durations[anim->frame_i];

        anim->quad.x = anim->frame_i * asset->frame_width;

        // Return true if an animation cycle has finished
        if (anim->frame_i - t.from == 0) return true;
    }

    return false;
}