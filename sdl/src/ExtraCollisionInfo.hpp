#pragma once

// This is used when the quad dimensions of the spritesheet are not the same as collision boxes we want,
// e.g. big quad of a player, but we only want the feet to be the collision box.
struct ExtraCollisionInfo {
    int offset_x;
    int offset_y;
    int w;
    int h;
};