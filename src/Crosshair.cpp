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

    // If the mouse moved, then update the crosshair according to the mouse coords,
    // otherwise, check joystick input.

    if (g_controls.MouseMoved()) {
        // Passing render_rect coords to GetMouseGameState and not x and y,
        // because x and y are floats, and casting pointers causes bugs.
        GetMouseGameState(& render_rect.x, & render_rect.y);
        x = render_rect.x;
        y = render_rect.y;
    }
    else {

        float joystick_xv = 0;
        float joystick_yv = 0;

        float joystick_xm = ControllerAxis(JOYSTICK_RIGHTX);
        float joystick_ym = ControllerAxis(JOYSTICK_RIGHTY);

        float joystick_m = pyth(joystick_xm, joystick_ym);

        if (joystick_m > AXIS_MIN_MOVED) {

            float sf = controller_crosshair_v / joystick_m * (joystick_m / AXIS_MAX);

            joystick_xv = joystick_xm * sf;
            joystick_yv = joystick_ym * sf;
        }

        x += joystick_xv * g_dt;
        y += joystick_yv * g_dt;

        render_rect.x = x;
        render_rect.y = y;
    }
}