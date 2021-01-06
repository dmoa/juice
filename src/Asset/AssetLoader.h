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

struct Asset_Ase {
    std::string file_path; // defacto name
    SDL_Texture* texture;
};

struct Asset_Ase_Animated : public Asset_Ase {
    //Asset_Ase_Animated() {};
    int frame_width;
    int frame_height;
    int num_frames;

    u16* frame_durations;
    std::unordered_map<std::string, Tag_Range> tags;
    // For now, there aren't any cases where an aniamted sprite doesn't have a collision box.
    // If a sprite is animated and doesn't need a collision box in the future, it would likely
    // be an edge case and we waste an obscure amount of memory when holding an empty pointer.
    SDL_Rect* collision_box;
};

inline Asset_Ase_Animated* LoadAsset_Ase(std::string file_path) {
    Ase_Output* output = Ase_Load(file_path);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(output->pixels, output->frame_width * output->num_frames, output->frame_height, 8, output->frame_width * output->num_frames, SDL_PIXELFORMAT_INDEX8);
    if (! surface) SDL_Log("Surface could not be created!, %s\n", SDL_GetError());
    SDL_SetPaletteColors(surface->format->palette, (SDL_Color*) & output->palette.entries, 0, output->palette.num_entries);
    SDL_SetColorKey(surface, SDL_TRUE, output->palette.color_key);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_window.rdr, surface);
    if (! texture) SDL_Log("Texture could not be created!, %s, %s\n", SDL_GetError(), file_path.c_str());
    SDL_FreeSurface(surface);

    Asset_Ase_Animated* asset = new Asset_Ase_Animated ({
        file_path,
        texture,
        output->frame_width,
        output->frame_height,
        output->num_frames,
        output->frame_durations,
        output->tags,
        new SDL_Rect
    });

    for (int i = 0; i < output->num_slices; i++) {
        if (output->slices[i].name == "Collision") {
            *(asset->collision_box) = output->slices[i].quad;
        } else {
            SDL_Log("Asset_Ase slice %s not supported", output->slices[i].name.c_str());
        }
    }

    // Not using Ase_Destroy_Output() because we still want to use
    // the tags and frame durations from output. Instead, we only delete the pixels
    // and the output container because the pixel data has been copied into SDL_Texture.
    delete [] output->pixels;
    delete [] output->slices;
    delete output;

    return asset;
}

inline void DestroyAsset_Ase(Asset_Ase* a) {
    SDL_DestroyTexture(a->texture);
  //  delete [] a->frame_durations;
 //   delete a->collision_box;
    delete a;
}