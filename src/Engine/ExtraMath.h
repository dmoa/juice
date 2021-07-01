#pragma once

#include <stdlib.h>
#include <time.h>

#define PI 3.14159265
#define ROOT2 1.41421356237
#define ToRadians(a) a*PI/180
typedef SDL_Point v2;

// Assuming all polygons have four sides (it's all we need for now)
#define POLYGON_NUM_POINTS 4

inline float pyth_s(float x, float y, float x2, float y2) {
    return (x-x2)*(x-x2) + (y-y2)*(y-y2);
}

inline float pyth(float a, float b) {
    return sqrt(a*a + b*b);
}

// min inclusive, max exclusive.
inline int random(int min, int max) {
    return rand() % (max - min) + min;
}

inline float min(float a, float b) {
    if (b < a) return b;
    return a;
}

inline float max(float a, float b) {
    if (b > a) return b;
    return a;
}

inline int abs(int n) {
    return (n<0) ? -n : n;
}

inline bool AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2) {
    return x + w > x2 && x < x2 + w2 && y + h > y2 && y < y2 + h2;
}

inline bool AABB(Asset_Ase* a, Asset_Ase* b, float x, float y, float x2, float y2) {
    return x + a->damage_box->x + a->damage_box->w > x2 + b->damage_box->x && x + a->damage_box->x < x2 + b->damage_box->x + b->damage_box->w && y + a->damage_box->y + a->damage_box->h > y2 + b->damage_box->y && y + a->damage_box->y < y2 + b->damage_box->y + b->damage_box->h;
}

inline bool AABB_Movement(float x, float y, float w, float h, Asset_Ase* a, float x2, float y2) {
    return x + w > x2 + a->movement_box->x && x < x2 + a->movement_box->x + a->movement_box->w && y + h > y2 + a->movement_box->y && y < y2 + a->movement_box->y + a->movement_box->h;
}

// This explains it better than I could: http://jeffreythompson.org/collision-detection/line-line.php
inline bool LineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {

    float a = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
    float b = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

    return a >= 0 && a <= 1 && b >= 0 && b <= 1;
}

inline bool LineRect(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh) {

    // check if the line has hit any of the rectangle's sides
    bool left = LineLine(x1, y1, x2, y2, rx, ry, rx, ry + rh);
    bool right = LineLine(x1, y1, x2, y2, rx + rw, ry, rx + rw, ry + rh);
    bool top = LineLine(x1, y1, x2, y2, rx, ry, rx + rw, ry);
    bool bottom = LineLine(x1, y1, x2, y2, rx, ry + rh, rx + rw, ry + rh);

    return left || right || top || bottom;
}

inline bool PointRect(float x, float y, SDL_Rect* rect) {
    return x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h;
}

// Not safe
inline void RectToV2(SDL_Rect* r, v2* vertices) {

    vertices[0] = {r->x, r->y};
    vertices[1] = {r->x + r->w, r->y};
    vertices[2] = {r->x + r->w, r->y + r->h};
    vertices[3] = {r->x, r->y + r->h};
}

// Assuming polygon has 4 sides for now
template <typename A, typename B>
inline bool PolygonPoint(v2* vertices, A px, B py) {

    bool collision = false;

    for (int i = 0; i < POLYGON_NUM_POINTS; i++) {

        v2 p1 = vertices[i];
        v2 p2 = vertices[(i + 1) % POLYGON_NUM_POINTS];

        if ((p1.y > py != p2.y > py) && px < (p2.x - p1.x) * (py - p1.y) / (p2.y - p1.y) + p1.x) {
            collision = ! collision;
        }
    }

    return collision;
}

template <typename A, typename B>
inline void RotatePoint(A* point_x, B* point_y, v2* source, float wrong_angle) {

    float radius = pyth(*point_x - source->x, *point_y - source->y);
    float angle = ToRadians(- wrong_angle);
    *point_x -= source->x; *point_y -= source->y;

    *point_x = source->x + *point_x * cos(angle) - *point_y * sin(angle);
    *point_y = source->y + *point_x * sin(angle) + *point_y * cos(angle);
}

// Trying to identify the problem
inline void RotatePoint(v2* point, v2* source, float wrong_angle) {
    float radius = pyth(point->x - source->x, point->y - source->y); // @Constant, seems to be fine
    printf("%f", radius);
    float angle = ToRadians(- wrong_angle); // Not even important whether angle is wrong, because the problem is that the rotated point is nowhere near where its meant to be anyway, so the angle is the least of our problems
    point->x -= source->x; point->y -= source->y;

    point->x = source->x + point->x * cos(angle)     - point->y * sin(angle);
    point->y = source->y + point->x * sin(angle) + point->y * cos(angle);
}

inline bool PolygonRectangle(v2* vertices, SDL_Rect* rect) {

    // @DONE Checks if every line of the polygon collides with the rectangle.
    // @DONE Checks if any point of the rectangle is inside the polygon - For rectangles engulfed by polygons
    // @DONE?! Checks if any point of the polygon is inside the rectangle - For polygons engulfed by rectangles

    for (int i = 0; i < POLYGON_NUM_POINTS; i++) {

        v2 p1 = vertices[i];
        v2 p2 = vertices[(i + 1) % POLYGON_NUM_POINTS];

        if (LineRect(p1.x, p1.y, p2.x, p2.y, rect->x, rect->y, rect->w, rect->h)) return true;
        if (PointRect(p1.x, p1.y, rect)) return true;
    }

    return PolygonPoint(vertices, rect->x, rect->y) || PolygonPoint(vertices, rect->x + rect->w, rect->y) || PolygonPoint(vertices, rect->x + rect->w, rect->y + rect->h) || PolygonPoint(vertices, rect->x, rect->y + rect->h);
}