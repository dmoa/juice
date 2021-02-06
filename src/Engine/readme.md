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
    std::string name;

    // Current Frame Index (Starting at 0)
    int frame_i;

    // Counter used to measure time until next frame.
    float tick;

    // Quad that contains information as to how to crop a sprite.
    SDL_Rect quad;
};

// If name is an actual animation name, that animation will be set as the current animation.
// Changes all values in CurAnimation appropriately.
inline void SetAnimation(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name);

// Only sets the animation if the name passed is not the current animation name.
// Useful to run every frame as to not spam SetAnimation() and constantly reset values in CurAnimation.
inline void SetAnimationIf(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name);

// Updates the current animation data according to the data in the asset passed.
// Returns true if the animation cycle has just finished.
inline bool UpdateAnimation(CurAnimation* anim, Asset_Ase_Animated* asset, float* dt);
```

## Asset.h <a id="Asset.h"></a>

```c++
// .ase Asset Struct
struct Asset_Ase {

    // Defacto name of the asset.
    std::string file_path;

    // Texture containing driver-specific organised pixel data.
    SDL_Texture* texture;

    // Not the same as width and height. Use GetTextureSize() from Graphics.h to get texture width and height.
    // If asset contains multiple frames, the frames are put side by side in the texture.
    // Frame width and height are the original sizes of these frames, not the new texture sizes.
    int frame_width;
    int frame_height;

    // For now, there aren't any cases where a sprite doesn't have a collision box, so every asset has a collision box.
    SDL_Rect* collision_box;

// .ase Animated Asset Struct
// Contains animation data while Asset_Ase does not.
struct Asset_Ase_Animated : Asset_Ase {

    // Number of frames in total across all the different animations in the asset.
    int num_frames;

    // The duration of each of those frames.
    u16* frame_durations;

    // Index by the name of the animation to get the .from and .to, the indexes of where that animation starts and ends.
    std::unordered_map<std::string, Tag_Range> tags;
    };
};

// Warning: Loading and Destroying assets of non-animated as animated and vice versa can cause memory leaks / segmentation faults.

// Loads a .ase asset on to the heap, and returning the pointer to it.
Asset_Ase* LoadAsset_Ase(std::string file_path);

// Identical functionality to LoadAsset_Ase, but also casting the pointer.
inline Asset_Ase_Animated* LoadAsset_Ase_Animated(std::string file_path);

// Destroy the contents that each pointer is pointing to respectively.
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
    float fpss [ACCURACY];
    int fpss_index;

    // Contains the average fps over ACCURACY amount of previous fps.
    int average_fps;

    // Calculates the new g_dt, average_fps. Should use in main loop.
    void tick();
};
```


## Controls.h <a id="Controls.h"></a>

```c++
// Gets the mouse coordinates converted into game coordinates.
inline void GetMouseGameState(int* x, int* y);

// Gets if a mouse button is down. 1 - left, 2 - middle, 3 - right.
inline bool GetMouseDown(int i = 1);

// Global Controls
struct GlobalControls {

    // Meant for internal use but can be accessed if needed.
    const Uint8* keys_down = NULL;
    SDL_GameController* controller = NULL;
    bool action_dev_before = false;

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

    // Left Ctrl Key || Controller Back Button and Pointing Left
    bool ActionDev();
};
extern GlobalControls g_controls;
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
```

## Graphics.h <a id="Graphics.h"></a>

```c++
// Gets the texture size.
inline void GetTextureSize(SDL_Texture* t, int* w, int* h);

// Renders the texture to the renderer with no cropping.
// pos can be either TOP_LEFT or CENTER, which picks the origin to draw from.
inline void RenderCopyWhole(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* _rt, DrawnFrom pos = TOP_LEFT);

// Prints to the screen. Only uses g_window.rdr renderer.
void PrintScreen(std::string text, int x, int y);
```

## Text.h <a id="Text.h"></a>

```c++
// Global Text Component
struct Text {

    // Loads a font, saving its address in main_font.
    // By default it looks in assets/font.ttf (relative to the executed path), but can be any path.
    void LoadFont(std::string path = "assets/font.ttf");

    // Destroys the font main_font is pointing to.
    void DestroyFont();

    // Creates a texture using text, main_font, and font_color.
    SDL_Texture* CreateTexture(std::string text);

    // Stores the font used for all things in the Text component.
    // If you would like to store more than one font, edit the Text struct, this component is very editable.
    TTF_Font* main_font = NULL;

    // The color used for all texture creation.
    // To edit it: g_text.font_color = .....
    SDL_Color font_color = {255, 255, 255};
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
};
```
