#include <SDL2/SDL.h>

struct Clock {
    // dt
    float last_tick_time = 0;
    float dt = 0;

    // for average fps
    float fpss [5] = {-1, -1, -1, -1, -1};
    int fpss_index = -1;
    int average_fps = -1;


    void tick() {
        float tick_time = SDL_GetTicks();
        dt = (tick_time - last_tick_time) / 1000;
        last_tick_time = tick_time;

        average_fps = (fpss[0]+fpss[1]+fpss[2]+fpss[3]+fpss[4]) / 5;
        if (dt != 0) fpss[fpss_index] = 1 / dt;
        fpss_index = (fpss_index + 1) % 5;
    }
};