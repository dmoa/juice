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

struct Asset_Ase {
    std::string file_path; // defacto name
    SDL_Texture* texture;
    int frame_width;
    int frame_height;

    // If a sprite in the future does not need a boxesz, it would likely
    // be an edge case and we waste an negligable amount of memory when holding empty pointers.
    SDL_Rect* movement_box;
    SDL_Rect* damage_box;
};

struct Asset_Ase_Animated : Asset_Ase {
    int num_frames;
    u16* frame_durations;
    std::unordered_map<std::string, Tag_Range> tags;
};


Asset_Ase* LoadAsset_Ase(std::string file_path);

inline Asset_Ase_Animated* LoadAsset_Ase_Animated(std::string file_path) {
    return (Asset_Ase_Animated*) LoadAsset_Ase(file_path);
}

inline void DestroyAsset_Ase(Asset_Ase* a) {
    SDL_DestroyTexture(a->texture);
    delete a->movement_box;
    delete a->damage_box;
    delete a;
}

inline void DestroyAsset_Ase_Animated(Asset_Ase_Animated* a) {
    delete a->frame_durations;
    // Copying out DestroyAsset_Ase because I'm not sure whether that
    // would make the compiler cast the pointer when it doesn't need to.
    SDL_DestroyTexture(a->texture);
    delete a->movement_box;
    delete a->damage_box;
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
        asset = new Asset_Ase_Animated ({
            file_path,
            texture,
            output->frame_width,
            output->frame_height,
            new SDL_Rect,
            new SDL_Rect,
            output->num_frames,
            output->frame_durations,
            output->tags
        });
    }
    else {
        asset = new Asset_Ase ({
            file_path,
            texture,
            output->frame_width,
            output->frame_height,
            new SDL_Rect,
            new SDL_Rect
        });
    }

    for (int i = 0; i < output->num_slices; i++) {
        if (output->slices[i].name == "movement_box") {
            *(asset->movement_box) = output->slices[i].quad;
        }
        else if (output->slices[i].name == "damage_box") {
            *(asset->damage_box) = output->slices[i].quad;
        }
        else {
            print("%s: Asset_Ase slice %s not supported", file_path.c_str(), output->slices[i].name.c_str());
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

#endif