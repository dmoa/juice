#include "Crosshair.h"

void Crosshair::LoadAsset() {
    texture = LoadAsset_IMG("assets/crosshair.png");
}

void Crosshair::DestroyAsset() {
    SDL_DestroyTexture(texture);
}

void Crosshair::Draw() {
    RenderCopyWhole(g_window.rdr, texture, & render_rect, CENTER);
}

void Crosshair::Update() {

    float joystick_xv = 0;
    float joystick_yv = 0;

    if (IsLeft(ControllerAxis(JOYSTICK_RIGHTX))) {
        joystick_xv = - controller_crosshair_v;
    }
    if (IsRight(ControllerAxis(JOYSTICK_RIGHTX))) {
        joystick_xv = controller_crosshair_v;
    }
    if (IsUp(ControllerAxis(JOYSTICK_RIGHTY))) {
        joystick_yv = - controller_crosshair_v;
    }
    if (IsDown(ControllerAxis(JOYSTICK_RIGHTY))) {
        joystick_yv = controller_crosshair_v;
    }

    if (joystick_xv && joystick_yv) {
        joystick_xv /= ROOT2;
        joystick_yv /= ROOT2;
    }

    x += joystick_xv * g_dt;
    y += joystick_yv * g_dt;

    render_rect.x = x;
    render_rect.y = y;
}