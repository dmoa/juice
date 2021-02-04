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

## How?

```c++
// main.cpp:
#define ENGINE_IMPLEMENTATION
#include <Engine/Engine.h>
// Which automatically defines:
Window window;
EngineClock engine_clock;

// Other files:
#include <Engine/Engine.h>

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

## Engine.h <a id="Engine.h"> testing </a>

```c++
// Initialises everything except window. For window, use window.Init().
inline void EngineInit();

// Quits everything except for window. For window, use window.Shutdown().
inline void EngineQuit();
```

## Animation.h

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
inline void SetAnimationIf(CurAnimation* anim, Asset_Ase_Animated* asset, std::string name)
```

## Asset.h

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

## Clock.h

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


## Controls.h

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
```

## ExtraMath.h

```c++

#define PI 3.14159265

// Pythagoras theroem but without the final square root, i.e. just a^2 + b^2.
// If you want high performance distance calculation, use this, and compare with your distance^2.
// This method is faster because squaring is faster than square rooting
inline float pyth_s(float x, float y, float x2, float y2);

// Random number between min and max (inclusive).
inline int random(int min, int max);

// Minimum of the two.
inline float min(float a, float b)

// Maximum of the two.
inline float max(float a, float b)

// AABB / Two Rectangle Collision Detection.
AABB(float x, float y, float w, float h, float x2, float y2, float w2, float h2);
```

## Graphics.h

```c++
// Gets the texture size.
inline void GetTextureSize(SDL_Texture* t, int* w, int* h);

// Renders the texture to the renderer with no cropping.
// pos can be either TOP_LEFT or CENTER, which picks the origin to draw from.
inline void RenderCopyWhole(SDL_Renderer* r, SDL_Texture* t, SDL_Rect* _rt, DrawnFrom pos = TOP_LEFT);

// Prints to the screen. Only uses g_window.rdr renderer.
void PrintScreen(std::string text, int x, int y);
```

## Text.h

```c++
// Source changing, documentated soon.
```


## Window.h

```c++
// Global Window Data
struct GlobalWindowData {
    int w;
    int h;
    int scale;
    SDL_Renderer* rdr;
    SDL_Rect gameplay_viewport;
};

// Window window is created in implementation.
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
