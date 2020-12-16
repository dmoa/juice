#pragma once

#include <string>

#include "../sdl.h"
#include "int.h"
#include "../Globals/Window.h"
#include "ase_loader.h"

inline SDL_Texture* LoadImage(SDL_Renderer* renderer, std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
    if (!texture) SDL_Log("%s%s", path.c_str(), " not found");
    return texture;
}

struct Asset_Ase {
    SDL_Texture* texture;
    Ase_Tag* tags;
    u16* frame_durations;
    int frame_width;
    int frame_height;
    int num_tags;
    int num_frames;
};

static Asset_Ase* LoadAsset_Ase(SDL_Renderer* renderer, std::string file_path) {
    Ase_Output* output = Ase_Load(file_path);

    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(output->pixels, output->frame_width * output->num_frames, output->frame_height, 8, output->frame_width * output->num_frames, SDL_PIXELFORMAT_INDEX8);
    if (! surface) SDL_Log("Surface could not be created!, %s\n", SDL_GetError());
    SDL_SetPaletteColors(surface->format->palette, (SDL_Color*) & output->palette.entries, 0, output->palette.num_entries);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(global_window_data.rdr, surface);
    if (! texture) SDL_Log("Texture could not be created!, %s, %s\n", SDL_GetError(), file_path.c_str());
    SDL_FreeSurface(surface);

    // Not using Ase_Destroy_Output() because we still want to use
    // the tags and frame durations from output. Instead, we only delete the pixels
    // and the output container because the pixel data has been copied into SDL_Texture.
    delete [] output->pixels;
    delete output;


    Asset_Ase* asset = new Asset_Ase {
        texture,
        output->tags,
        output->frame_durations,
        output->frame_width,
        output->frame_height,
        output->num_tags,
        output->num_frames
    };

    return asset;
}

inline void DestroyAsset_Ase(Asset_Ase* a) {
    SDL_DestroyTexture(a->texture);
    delete [] a->tags;
    delete [] a->frame_durations;
    delete a;
}