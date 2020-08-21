#include "AABB.hpp"

bool AABB(int x, int y, int w, int h, int x2, int y2, int w2, int h2) {
    return x + w >= x2 && x <= x2 + w2 && y + h >= y2 && y <= y2 + h2;
}