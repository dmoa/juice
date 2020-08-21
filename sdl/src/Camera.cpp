#include "Camera.hpp"

void Camera::ChangePosX(float x) {
    real_x += x;
    viewport.x = real_x;
}

void Camera::ChangePosY(float y) {
    real_y += y;
    viewport.y = real_y;
}

void Camera::UpdateSize(int w, int h) {
    viewport.w = w;
    viewport.h = h;
}

SDL_Rect* Camera::GetViewport() {
    return & viewport;
}