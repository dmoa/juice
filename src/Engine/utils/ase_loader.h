/*
Aseprite Loader
Copyright © 2020 Stan O

MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Parses:
    - All header data
    - All frame data
    - All pixel data

Chunks Supported:
    - CEL
        - No opacity support
    - PALETTE 0x2019
        - No name support
    - SLICE 0x2022
        - Does not support 9 patches or pivot flags
        - Loads only first slice key


- Only supports indexed color mode
- Only supports zlib compressed pixel data

- Does not support blend mode
- Does not support layers

Let me know if you want something added,
    ~ Stan

*/

// @NOTE:
// I've edited this library so that the wrapper AssetLoader.h is smaller.

#pragma once

#include <stdio.h>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include <Engine/Engine.h>
#include "decompressor.h"

inline u16 GetU16(char* memory) {
	u8* p = (u8*)(memory);
	return (((u16)p[1]) << 8) |
		   (((u16)p[0]));
}

inline u32 GetU32(void* memory) {
	u8* p = (u8*)(memory);
	return (((u32)p[3]) << 24) |
		   (((u32)p[2]) << 16) |
		   (((u32)p[1]) <<  8) |
		   (((u32)p[0]));
}

#define HEADER_MN 0xA5E0
#define FRAME_MN 0xF1FA

#define HEADER_SIZE 128
#define FRAME_SIZE 16

#define OLD_PALETTE_1 0x0004 // depricated
#define OLD_PALETTE_2 0x0011 // depricated
#define LAYER 0x2004
#define CEL 0x2005
#define CEL_EXTRA 0x2006
#define COLOR_PROFILE 0x2007
#define MASK 0x2016 // depricated
#define PATH 0x2017 // depricated
#define TAGS 0x2018
#define PALETTE 0x2019
#define USER_DATA 0x2020
#define SLICE 0x2022

#define INDEX_FORMAT 2 // indexed color format flag

struct Ase_Header {
    u32 file_size;
    u16 magic_number;
    u16 num_frames;
    u16 width;
    u16 height;
    u16 color_depth;    // 32 RGBA, 16 Grayscale, 8 Indexed
    u32 flags;          // 1 = layer opacity valid
    u16 speed;          // frame speed, depricated
    u8  palette_entry;  // the one transparent colour for indexed sprites only
    u16 num_colors;

    // Pixel ratio. Default 1:1.
    u8  pixel_width;
    u8  pixel_height;

    // Rendered grid for aseprite, not for asset loading.
    s16 x_grid;
    s16 y_grid;
    u16 grid_width;
    u16 grid_height;
};

struct Ase_Frame {
    u32 num_bytes;
    u16 magic_number;
    u16 old_num_chunks; // old specifier of number of chunks
    u16 frame_duration;
    u32 new_num_chunks; // number of chunks, if 0, use old field.
};

// Need to fix, for now assuming .ase are indexed sprites,
// but will need to change in the future as there won't always be 256 entries.
struct Palette_Chunk {
    u32 num_entries;
    u8 color_key;
    SDL_Color entries [256];
};

struct Tag_Range {
    char* name;
    u16 from;
    u16 to;
};

struct Slice {
    char* name;
    SDL_Rect quad;
};

struct Ase_Output {
    u8* pixels;
    u16 frame_width;
    u16 frame_height;
    Palette_Chunk palette;

    Tag_Range* tags;
    u16 num_tags;

    u16* frame_durations;
    u16 num_frames;

    Slice* slices;
    u32 num_slices;
};

inline void Ase_Destroy_Output(Ase_Output* output);

static Ase_Output* Ase_Load(std::string path) {

    std::ifstream file(path, std::ifstream::binary);

    if (file) {

        file.seekg(0, file.end);
        const int file_size = file.tellg();

        char buffer [file_size];
        char* buffer_p = & buffer[HEADER_SIZE];

        // transfer data from file into buffer and close file
        file.seekg(0, std::ios::beg);
        file.read(buffer, file_size);
        file.close();

        Ase_Header header = {
            GetU32(& buffer[0]),
            GetU16(& buffer[4]),
            GetU16(& buffer[6]),
            GetU16(& buffer[8]),
            GetU16(& buffer[10]),
            GetU16(& buffer[12]),
            GetU32(& buffer[14]),
            GetU16(& buffer[18]),
            (u8) buffer[28],
            GetU16(& buffer[32]),
            (u8) buffer[34],
            (u8) buffer[35],
            (s16) GetU16(& buffer[36]),
            (s16) GetU16(& buffer[38]),
            GetU16(& buffer[40]),
            GetU16(& buffer[42])
        };

        if (header.color_depth != 8) {
            print("%s: Not in indexed color mode. Only indexed color mode supported.\n", path.c_str());
            return NULL;
        }

        Ase_Output* output = bmalloc(Ase_Output);
        output->pixels = bmalloc_arr(u8, header.width * header.height * header.num_frames);
        output->frame_width = header.width;
        output->frame_height = header.height;
        output->palette.color_key = header.palette_entry;

        output->frame_durations = bmalloc_arr(u16, header.num_frames);
        output->num_frames = header.num_frames;

        // Because we are using malloc, we cannot use default values in struct because
        // the memory that we are given has garbage values, so we have to manually set
        // the values here.
        output->tags = NULL;
        output->num_tags = 0;
        output->slices = NULL;
        output->num_slices = 0;

        // Aseprite doesn't tell us upfront how many slices we're given,
        // so there's no way really of creating the array of size X before
        // we receive all the slices. Vector is used temporarily, but then
        // converted into Slice* for output.
        std::vector<Slice> temp_slices;

        // This helps us with formulating output but not all frame data is needed for output.
        Ase_Frame frames [header.num_frames];

        // fill the pixel indexes in the frame with transparent color index
        for (int i = 0; i < header.width * header.height * header.num_frames; i++) {
            output->pixels[i] = header.palette_entry;
        }

        // Each frame may have multiple chunks, so we first get frame data, then iterate over all the chunks that the frame has.
        for (int i = 0; i < header.num_frames; i++) {

            frames[i] = {
                GetU32(buffer_p),
                GetU16(buffer_p + 4),
                GetU16(buffer_p + 6),
                GetU16(buffer_p + 8),
                GetU32(buffer_p + 12)
            };
            output->frame_durations[i] = frames[i].frame_duration;

            if (frames[i].magic_number != FRAME_MN) {
                print("%s: Frame %i magic number not correct, corrupt file?\n", path.c_str(), i);
                Ase_Destroy_Output(output);
                return NULL;
            }

            buffer_p += FRAME_SIZE;


            for (int j = 0; j < frames[i].new_num_chunks; j++) {

                u32 chunk_size = GetU32(buffer_p);
                u16 chunk_type = GetU16(buffer_p + 4);

                switch (chunk_type) {

                    case PALETTE: {
                        output->palette.num_entries = GetU32(buffer_p + 6);
                        // specifies the range of unique colors in the palette
                        // There may be many repeated colors, so range -> efficient.
                        u32 first_to_change = GetU32(buffer_p + 10);
                        u32  last_to_change = GetU32(buffer_p + 14);

                        for (int k = first_to_change; k < last_to_change + 1; k++) {

                            // We do not support color data with strings in it. Flag 1 means there's a name.
                            if (GetU16(buffer_p + 26) == 1) {
                                print("%s: Name flag detected, cannot load! Color Index: %i.\n", path.c_str(), k);
                                Ase_Destroy_Output(output);
                                return NULL;
                            }
                            output->palette.entries[k] = {buffer_p[28 + k*6], buffer_p[29 + k*6], buffer_p[30 + k*6], buffer_p[31 + k*6]};
                        }
                        break;
                    }

                    case CEL: {
                        s16 x_offset = GetU16(buffer_p + 8);
                        s16 y_offset = GetU16(buffer_p + 10);
                        u16 cel_type = GetU16(buffer_p + 13);

                        if (cel_type != INDEX_FORMAT) {
                            print("%s: Pixel format not supported!\n", path.c_str());
                            Ase_Destroy_Output(output);
                            return NULL;
                        }

                        u16 width  = GetU16(buffer_p + 22);
                        u16 height = GetU16(buffer_p + 24);
                        u8 pixels [width * height];

                        unsigned int data_size = Decompressor_Feed(buffer_p + 26, 26 - chunk_size, pixels, width * height, true);
                        if (data_size == -1) {
                            print("%s: Failed to decompress pixels!\n", path.c_str());
                            Ase_Destroy_Output(output);
                            return NULL;
                        }

                        // transforming array of pixels onto larger array of pixels
                        const int pixel_offset = header.width * header.num_frames * y_offset + i * header.width + x_offset;

                        for (int k = 0; k < width * height; k ++) {
                            int index = pixel_offset + k%width + floor(k / width) * header.width * header.num_frames;
                            output->pixels[index] = pixels[k];
                        }

                        break;
                    }

                    case TAGS: {
                        output->num_tags = GetU16(buffer_p + 6);
                        output->tags = bmalloc_arr(Tag_Range, output->num_tags);

                        // iterate over each tag and append data to output->tags
                        int tag_buffer_offset = 0;
                        for (int k = 0; k < output->num_tags; k ++) {

                            u16 slen = GetU16(buffer_p + tag_buffer_offset + 33);
                            // + 1 because aseprite doesn't use null terminating strings, so we have to make them ourselves :/
                            char* tag_name = bmalloc_arr(char, slen + 1);
                            for (u16 a = 0; a < slen; a++) {
                                tag_name[a] = *(buffer_p + tag_buffer_offset + a + 35);
                            }
                            tag_name[slen] = '\0';

                            output->tags[k] = {
                                tag_name,
                                GetU16(buffer_p + tag_buffer_offset + 16), // .from
                                GetU16(buffer_p + tag_buffer_offset + 18)  // .to
                            };

                            tag_buffer_offset += 19 + slen;
                        }
                        break;
                    }
                    case SLICE: {
                        u32 num_keys = GetU32(buffer_p + 6);
                        u32 flag = GetU32(buffer_p + 10);
                        if (flag != 0) {
                            print("%s: Flag %i not supported!\n", path.c_str(), flag);
                            Ase_Destroy_Output(output);
                            return NULL;
                        }

                        // For now, we assume that the slice is the same
                        // throughout all the frames, so we don't care about
                        // the starting frame_number.
                        // int frame_number = GetU32(buffer_p + 20 + slen);

                        u16 slen = GetU16(buffer_p + 18);
                        char* name = bmalloc_arr(char, slen + 1);
                        for (u16 a = 0; a < slen; a++) {
                            name[a] = *(buffer_p + 20 + a);
                        }
                        name[slen] = '\0';

                        SDL_Rect quad = {
                            (s32) GetU32(buffer_p + slen + 24),
                            (s32) GetU32(buffer_p + slen + 28),
                            GetU32(buffer_p + slen + 32),
                            GetU32(buffer_p + slen + 36)
                        };

                        temp_slices.push_back({name, quad});

                        break;
                    }

                    default: break;
                }
                buffer_p += chunk_size;
            }
        }


        // convert vector to array for output
        output->slices = bmalloc_arr(Slice, temp_slices.size());
        for (int i = 0; i < temp_slices.size(); i ++) {
            output->slices[i] = temp_slices[i];
        }
        output->num_slices = temp_slices.size();

        return output;

    } else {
        print("%s: File could not be loaded.\n", path.c_str());
        return NULL;
    }
}

inline void Ase_Destroy_Output(Ase_Output* output) {
    free(output->pixels);
    free(output->frame_durations);

    for (int i = 0; i < output->num_slices; i++) {
        free(output->slices[i].name);
    }
    for (int i = 0; i < output->num_tags; i++) {
        free(output->tags[i].name);
    }

    free(output->slices);
    free(output->tags);

    free(output);
}