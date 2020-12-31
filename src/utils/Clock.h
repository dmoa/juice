#include <SDL2/SDL.h>

// The more fps we store, the more accurate the average fps.
#define ACCURACY 50

struct Clock {
    // dt
    float last_tick_time = 0;
    float dt = 0;

    // for average fps
    float fpss [ACCURACY];
    int fpss_index = -1;
    int average_fps = -1;


    void tick() {
        float tick_time = SDL_GetTicks();
        dt = (tick_time - last_tick_time) / 1000;
        last_tick_time = tick_time;

        float sum = 0;
        for (int i = 0; i < ACCURACY; i++) {
            sum += fpss[i];
        }
        average_fps = sum / ACCURACY;

        if (dt != 0) fpss[fpss_index] = 1 / dt;
        fpss_index = (fpss_index + 1) % ACCURACY;
    }
};