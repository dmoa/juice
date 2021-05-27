#include "Crosshair.h"
#include "Player.h"

void Crosshair::GivePointers(Player* _player) {
    player = _player;
}

void Crosshair::LoadAsset() {
    texture = LoadAsset_IMG("assets/crosshair.png");
}

void Crosshair::DestroyAsset() {
    SDL_DestroyTexture(texture);
}

void Crosshair::Draw() {
    if (is_drawn) RenderCopyWhole(g_window.rdr, texture, & render_rect, CENTER);
}

void Crosshair::Update() {

    // If the mouse moves or we've been using the mouse before, then update the crosshair according to the mouse coords.
    if (g_controls.MouseMoved() || ! last_move_with_controller) {

        last_move_with_controller = false;
        // Passing render_rect coords to GetMouseGameState and not x and y,
        // because x and y are floats, and casting pointers causes bugs.
        GetMouseGameState(& render_rect.x, & render_rect.y);
        x = render_rect.x;
        y = render_rect.y;
    }

    // Checking whether the joystick has been used:

    float joystick_x = 0;
    float joystick_y = 0;

    float joystick_xm = ControllerAxis(JOYSTICK_RIGHTX);
    float joystick_ym = ControllerAxis(JOYSTICK_RIGHTY);
    float joystick_m = pyth(joystick_xm, joystick_ym);

    if (joystick_m > AXIS_MIN_MOVED) {

        last_move_with_controller = true;

        float sf = controller_crosshair_r / joystick_m;

        joystick_x = joystick_xm * sf;
        joystick_y = joystick_ym * sf;

        x = player->GetDrawCenterX() + joystick_x;
        y = player->GetDrawCenterY() + joystick_y;
    }

    // We draw the controller if it was moved with the mouse, or, the joystick hits a minimum bar of movement.
    is_drawn = (! last_move_with_controller) || (last_move_with_controller && (joystick_x || joystick_y));

    render_rect.x = x;
    render_rect.y = y;
}