# Engine

## Contents
- [How?](#How?)
- [Engine.h](#Engine.h)
- [Animation.h](#Animation.h)
- [Asset.h](#Asset.h)
- [Clock.h](#Clock.h)
- [Controls.h](#Controls.h)
- [ExtraMath.h](#ExtraMath.h)
- [Graphics.h](#Graphics.h)
- [Text.h](#Text.h)
- [Window.h](#Window.h)
<hr>

## How? <a id="How?"></a>

```c++
// main.cpp:
#define ENGINE_IMPLEMENTATION
#include <Engine/Engine.h>
// Also automatically defines:
Window window;
EngineClock engine_clock;

// Other cpp files in project:
#include <Engine/Engine.h>
// Also gives access to globals:
float g_dt;
GlobalWindowData g_window;
GlobalControls g_controls;

// Or if you only want a specific component:
#include "Animation.h"
#include "Asset.h"
#include "Clock.h"
#include "Controls.h"
#include "ExtraMath.h"
#include "Graphics.h"
#include "Text.h"
#include "Window.h"
```

## Engine.h <a id="Engine.h"></a>

```c++
// Initialises everything except window. For window, use window.Init().
inline void EngineInit();

// Quits everything except for window. For window, use window.Shutdown().
inline void EngineQuit();
```

## Animation.h <a id="Animation.h"></a>

```c++
// Animation Struct
struct CurAnimation {

    // Name of the current animation being cycled through.
    char* name;

    // Current Frame Index (Starting at 0)
    int frame_i;

    // Counter used to measure time until next frame.
    float tick;

    // Quad that contains information as to how to crop a sprite.
    SDL_Rect quad;
};

// If name is an actual animation name, that animation will be set as the current animation.
// Changes all values in CurAnimation appropriately.
inline void SetAnimation(CurAnimation* anim, Asset_Ase_Animated* asset, char* name);

// Only sets the animation if the name passed is not the current animation name.
// Useful to run every frame as to not spam SetAnimation() and constantly reset values in CurAnimation.
inline void SetAnimationIf(CurAnimation* anim, Asset_Ase_Animated* asset, char* name);

// Updates the current animation data according to the data in the asset passed.
// Returns true if the animation cycle has just finished.
inline bool UpdateAnimation(CurAnimation* anim, Asset_Ase_Animated* asset);
```

## Asset.h <a id="Asset.h"></a>

```c++

inline SDL_Texture* LoadAsset_IMG(char* path);

struct Tags {
    Tag_Range* tags; // Tag_Range struct located in Ase_Loader.h
    u16 num_tags;
};

// .ase Asset Struct
struct Asset_Ase {

    // Defacto name of the asset.
    char* file_path;

    // Texture containing driver-specific organised pixel data.
    SDL_Texture* texture;

    // Not the same as width and height. Use GetTextureSize() from Graphics.h to get texture width and height.
    // If asset contains multiple frames, the frames are put side by side in the texture.
    // Frame width and height are the original sizes of these frames, not the new texture sizes.
    int frame_width;
    int frame_height;

    // For the draw order and for where an asset / entity can be damaged
    SDL_Rect* movement_box;
    // Used by the asset / entity to damage other assets / entities.
    SDL_Rect* damage_box;

// .ase Animated Asset Struct
// Contains animation data while Asset_Ase does not.
struct Asset_Ase_Animated : Asset_Ase {

    // Number of frames in total across all the different animations in the asset.
    int num_frames;

    // The duration of each of those frames.
    u16* frame_durations;

    Tags tags;
};


// Loads .ase asset & returns its address.
Asset_Ase* LoadAsset_Ase(char* file_path);

// Identical functionality to LoadAsset_Ase, but also casts the pointer.
inline Asset_Ase_Animated* LoadAsset_Ase_Animated(char* file_path);

// Destroy the contents that each pointer is pointing to respectively.
// Warning: Loading and Destroying assets of non-animated as animated and vice versa can cause memory leaks / segmentation faults.
inline void DestroyAsset_Ase(Asset_Ase* a);
inline void DestroyAsset_Ase_Animated(Asset_Ase_Animated* a);
```

## Clock.h <a id="Clock.h"></a>

```c++
// Global Delta Time
extern float g_dt;

// EngineClock engine_clock defined in implementation.
struct EngineClock {

    // Internal use
    float last_tick_time;
    // for average fps
    float fpss [ACCURACY];
    int fpss_index = -1;
    int average_fps = -1;

    // Calculates the new g_dt & average_fps. Should be used in the main loop.
    void tick();
};
```


## Controls.h <a id="Controls.h"></a>

```c++

// For uniformity and to bridge the gap between SDL and this Engine.
#define GetMouseState SDL_GetMouseState
#define JOYSTICK_LEFTX SDL_CONTROLLER_AXIS_LEFTX
#define JOYSTICK_LEFTY SDL_CONTROLLER_AXIS_LEFTY
#define JOYSTICK_RIGHTX SDL_CONTROLLER_AXIS_RIGHTX
#define JOYSTICK_RIGHTY SDL_CONTROLLER_AXIS_RIGHTY

// minimum magnitude required to consider the joystick "triggered".
#define AXIS_MIN_MOVED 7000
// Maximum value the axis can give us
#define AXIS_MAX 32767

// Global Controls
struct GlobalControls {

    // Meant for internal use but can be accessed if needed.
    const Uint8* keys_down = NULL;
    SDL_GameController* controller = NULL;
    bool action_dev_before = false;
    int old_mouse_x, old_mouse_y = 0;

    // Initialise keyboard and controller if available.
    void Init();

    // Left Arrow || A Key || Joystick Pointing Left
    bool Left();

    // Right Arrow || D Key || Joystick Pointing Right
    bool Right();

    // Up Arrow || W Key || Joystick Pointing Up
    bool Up();

    // Down Arrow || S Key || Joystick Pointing Down
    bool Down();

    // Left Mouse Click || Controller X Button
    bool Action1();

    // Escape Key || Controller Start Button
    bool Back();

    bool MouseMoved();

    // Left Ctrl Key || Controller Back Button and Pointing Left
    bool ActionDev();
};
extern GlobalControls g_controls;

// Gets the mouse coordinates converted into game coordinates.
inline void GetMouseGameState(int* x, int* y);

// Gets if a mouse button is down. 1 - left, 2 - middle, 3 - right.
inline bool GetMouseDown(int i = 1);

// Functions with same functionality, but the names makes it slightly clearer when running them.
inline bool IsLeft(s16 value) { return value < - AXIS_MIN_MOVED; };
inline bool IsRight(s16 value) { return value > AXIS_MIN_MOVED; };
inline bool IsUp(s16 value) { return value < - AXIS_MIN_MOVED; };
inline bool IsDown(s16 value) { return value > AXIS_MIN_MOVED; };

inline s16 ControllerAxis(SDL_GameControllerAxis button) { return SDL_GameControllerGetAxis(g_controls.controller, button); }
inline bool ControllerButton(SDL_GameControllerButton button) { return SDL_GameControllerGetButton(g_controls.controller, button); }
```

## ExtraMath.h <a id="ExtraMath.h"></a>

```c++

#define PI 3.14159265

// Pythagoras theroem but without the final square root, i.e. just a^2 + b^2.
// If you want high performance distance calculation, use this, and compare with your distance^2.
// This method is faster because squaring is faster than square rooting
inline float pyth_s(float x, float y, float x2, float y2);

// Random number between min (inclusive) and max (exclusive).
inline int random(int min, int max);

// Minimum of the two.
inline float min(float a, float b);

// Maximum of the two.
inline float max(float a, float b);

// AABB / Two Rectangle Collision Detection.
// Returns true if the rectangles overlap.
inline bool AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2);

// AABB but uses asset damage box.
inline bool AABB(Asset_Ase* a, Asset_Ase* b, float x, float y, float x2, float y2);
// AABB but uses movement box.
inline bool AABB_Movement(float x, float y, float w, float h, Asset_Ase* a, float x2, float y2);

```

## Graphics.h <a id="Graphics.h"></a>

```c++
// Gets the texture size.
inline void GetTextureSize(SDL_Texture* t, int* w, int* h);

// Renders the texture to the renderer with no cropping.
// pos can be either TOP_LEFT or CENTER, which picks the origin to draw from.
inline void RenderCopyWhole(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* _rt, DrawnFrom pos = TOP_LEFT);

// RenderCopy but does not stretch the item.
// Takes the width and height from the quad (src_r) and uses it for the destination rectangle internally.
inline void RenderCopy(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* src_r, float x, float y);

// Prints to the screen. Only uses g_window.rdr renderer.
void PrintScreen(char* text, int x, int y);
```

## Text.h <a id="Text.h"></a>

```c++
// Global Text Component
struct Text {

    // Loads a font, saving its address in main_font.
    // By default it looks in assets/font.ttf (relative to the executed path), but can be any path.
    void LoadFont(char* path = "assets/font.ttf");

    // Destroys the font main_font is pointing to.
    void DestroyFont();

    // Creates a texture using text, main_font, and font_color.
    SDL_Texture* CreateTexture(char* text);

    // Stores the font used for all things in the Text component.
    // If you would like to store more than one font, edit the Text struct, this component is very editable.
    TTF_Font* main_font = NULL;

    // The color used for all texture creation.
    // To edit it: g_text.font_color = .....
    SDL_Color font_color = {255, 255, 255};

    // Easily editable default font size which is used in LoadFont.
    const int default_font_size = 10;
};
extern Text g_text;
```


## Window.h <a id="Window.h"></a>

```c++
// Global Window Data
struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    SDL_Rect gameplay_viewport;
};
extern GlobalWindowData g_window;

// Window window is defined in implementation.
struct Window {

    // Creates window using information from g_window.
    void Init();

    // Clears window and other_texture.
    void Clear();

    // Sets the current render target to gameplay_texture - texture is scaled and cropped to game camera.
    void SetDrawGameplay();

    // Sets the current render target to other_texture - texture is scaled but not cropped.
    void SetDrawOther();

    // Renders gameplay_texture and other_texture to the window.
    void Present();

    // Destroys the icon, renderer, and window.
    void Shutdown();

    // Internal use
    SDL_Texture* gameplay_texture;
    SDL_Texture* other_texture;
    SDL_Rect other_texture_rect;
    SDL_Window* window;
    SDL_Surface* icon;
};
```
