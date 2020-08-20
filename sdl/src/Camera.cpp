#include "Camera.hpp"

void Camera::UpdateViewport(int x, int y, int w, int h) {
    viewport.x = x;
    viewport.y = y;
    viewport.w = w;
    viewport.h = h;
}

SDL_Rect* Camera::GetViewport() {
    return & viewport;
}