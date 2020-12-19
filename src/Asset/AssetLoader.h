#pragma once

#include <string>
#include <unordered_map>

#include <SDL_CP.h>
#include "../Globals/Window.h"
#include "ase_loader.h"

inline SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) SDL_Log("%s%s", path.c_str(), " not found");
    return texture;
}

struct Tag_Range {
    u16 from;
    u16 to;
};

struct Asset_Ase {
    SDL_Texture* texture;
    int frame_width;
    int frame_height;
    int num_frames;

    std::unordered_map<std::string, Tag_Range> tags;
    u16* frame_durations;
    SDL_Rect* collision_box;
};

// @TODO Add Slice to Asset_Ase, and add it in DestroyAsset_Ase
inline Asset_Ase* LoadAsset_Ase(std::string file_path) {
    Ase_Output* output = Ase_Load(file_path);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(output->pixels, output->frame_width * output->num_frames, output->frame_height, 8, output->frame_width * output->num_frames, SDL_PIXELFORMAT_INDEX8);
    if (! surface) SDL_Log("Surface could not be created!, %s\n", SDL_GetError());
    SDL_SetPaletteColors(surface->format->palette, (SDL_Color*) & output->palette.entries, 0, output->palette.num_entries);
    SDL_SetColorKey(surface, SDL_TRUE, output->palette.color_key);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(global_window_data.rdr, surface);
    if (! texture) SDL_Log("Texture could not be created!, %s, %s\n", SDL_GetError(), file_path.c_str());
    SDL_FreeSurface(surface);

    Asset_Ase* asset = new Asset_Ase {
        texture,
        output->frame_width,
        output->frame_height,
        output->num_frames,

        {},
        output->frame_durations,
        new SDL_Rect
    };

    for (int i = 0; i < output->num_tags; i++) {
        asset->tags[output->tags[i].name] = {output->tags[i].from, output->tags[i].to};
    }

    for (int i = 0; i < output->num_slices; i++) {
        if (output->slices[i].name == "collision") {
            *(asset->collision_box) = output->slices[i].quad;
        } else {
            SDL_Log("Asset_Ase slice %s not supported", output->slices[i].name.c_str());
        }
    }

    // Not using Ase_Destroy_Output() because we still want to use
    // the tags and frame durations from output. Instead, we only delete the pixels
    // and the output container because the pixel data has been copied into SDL_Texture.
    delete [] output->pixels;
    delete [] output->tags;
    delete output;

    return asset;
}

inline void DestroyAsset_Ase(Asset_Ase* a) {
    SDL_DestroyTexture(a->texture);
    delete [] a->frame_durations;
    delete a;
}