#pragma once

#include <string>
#include <unordered_map>

#include "Engine.h"
#include "utils/ase_loader.h"

inline SDL_Texture* LoadAsset_IMG(std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(g_window.rdr, path.c_str());
    if (!texture) print("%s%s", path.c_str(), " not found");
    return texture;
}

struct Tags {
    Tag_Range* tags;
    u16 num_tags;
};

struct Asset_Ase {
    char* file_path; // defacto name
    SDL_Texture* texture;
    int frame_width;
    int frame_height;

    // If a sprite in the future does not need a boxes, it would likely
    // be an edge case and we waste an negligable amount of memory when holding empty pointers.
    SDL_Rect* movement_box;
    SDL_Rect* damage_box;
};

struct Asset_Ase_Animated : Asset_Ase {
    int num_frames;
    u16* frame_durations;
    Tags tags;
};


Asset_Ase* LoadAsset_Ase(std::string file_path);

inline Asset_Ase_Animated* LoadAsset_Ase_Animated(std::string file_path) {
    return (Asset_Ase_Animated*) LoadAsset_Ase(file_path);
}

inline void DestroyAsset_Ase(Asset_Ase* a) {
    free(a->file_path);
    SDL_DestroyTexture(a->texture);
    free(a->movement_box);
    free(a->damage_box);

    free(a);
}

inline void DestroyAsset_Ase_Animated(Asset_Ase_Animated* a) {
    // Copying out DestroyAsset_Ase because if we don't then we free a before we can free frame_durations and tags.
    free(a->file_path);
    SDL_DestroyTexture(a->texture);
    free(a->movement_box);
    free(a->damage_box);

    free(a->frame_durations);

    for (int i = 0; i < a->tags.num_tags; i++) {
        free(a->tags.tags[i].name);
    }
    // We try to free instead of freeing because assets that do not have any tags loaded do never run malloc, which means that output->tags will be a NULL pointer if an asset has not assets.
    tryfree(a->tags.tags);

    free(a);
}

#ifdef ENGINE_IMPLEMENTATION

Asset_Ase* LoadAsset_Ase(std::string file_path) {

    Ase_Output* output = Ase_Load(file_path);
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(output->pixels, output->frame_width * output->num_frames, output->frame_height, 8, output->frame_width * output->num_frames, SDL_PIXELFORMAT_INDEX8);
    if (! surface) print("Surface could not be created!, %s\n", SDL_GetError());
    SDL_SetPaletteColors(surface->format->palette, (SDL_Color*) & output->palette.entries, 0, output->palette.num_entries);
    SDL_SetColorKey(surface, SDL_TRUE, output->palette.color_key);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_window.rdr, surface);
    if (! texture) print("Texture could not be created!, %s, %s\n", SDL_GetError(), file_path.c_str());
    SDL_FreeSurface(surface);

    Asset_Ase* asset;
    if (output->num_frames > 1) {
        Asset_Ase_Animated* _asset = bmalloc(Asset_Ase_Animated);
        *_asset =  {
            strmalloc_wt(file_path.c_str()),
            texture,
            output->frame_width,
            output->frame_height,
            bmalloc(SDL_Rect),
            bmalloc(SDL_Rect),
            output->num_frames,
            output->frame_durations,
            {output->tags, output->num_tags}
        };
        asset = (Asset_Ase*) _asset;
    }
    else {
        asset = bmalloc(Asset_Ase);
        *asset = {
            strmalloc_wt(file_path.c_str()),
            texture,
            output->frame_width,
            output->frame_height,
            bmalloc(SDL_Rect),
            bmalloc(SDL_Rect)
        };

        tryfree(output->tags);
        for (int i = 0; i < output->num_tags; i++) {
            free(output->tags[i].name);
        }
    }

    for (int i = 0; i < output->num_slices; i++) {
        if (strequal(output->slices[i].name, "movement_box")) {
            *(asset->movement_box) = output->slices[i].quad;
        }
        else if (strequal(output->slices[i].name, "damage_box")) {
            *(asset->damage_box) = output->slices[i].quad;
        }
        else {
            print("%s: Asset_Ase slice %s not supported", file_path.c_str(), output->slices[i].name);
        }
    }

    // Not using Ase_Destroy_Output() because we still want to use
    // the tags and frame durations from output. Instead, we only delete the pixels
    // and the output container because the pixel data has been copied into SDL_Texture.
    free(output->pixels);
    for (int i = 0; i < output->num_slices; i++) {
        free(output->slices[i].name);
    }
    free(output->slices);
    free(output);


    return asset;
}

#endif