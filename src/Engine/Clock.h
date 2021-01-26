#include <SDL2/SDL.h>

// The more previous fps we store, the more accurate the average fps.
#define ACCURACY 50

extern float g_dt;

struct EngineClock {
    // dt
    float last_tick_time = 0;

    // for average fps
    float fpss [ACCURACY];
    int fpss_index = -1;
    int average_fps = -1;

    void tick() {
        float tick_time = SDL_GetTicks();
        g_dt = (tick_time - last_tick_time) / 1000;
        last_tick_time = tick_time;

        float sum = 0;
        for (int i = 0; i < ACCURACY; i++) {
            sum += fpss[i];
        }
        average_fps = sum / ACCURACY;

        if (g_dt != 0) fpss[fpss_index] = 1 / g_dt;
        fpss_index = (fpss_index + 1) % ACCURACY;
    }
};
// odd naming to avoid collision with clock() in <time.h>
extern EngineClock engine_clock;

#ifdef ENGINE_IMPLEMENTATION
float g_dt = 0.f;
EngineClock engine_clock;
#endif