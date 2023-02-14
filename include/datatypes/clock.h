#ifndef SENGINE_CLOCK_H
#define SENGINE_CLOCK_H

#include <SDL.h>

struct Clock
{
    Uint64 previousTicks;
    float elapsedSeconds;

    int Tick() {
        const Uint64 currentTicks = SDL_GetPerformanceCounter();
        const Uint64 delta = (currentTicks - previousTicks);
        previousTicks = currentTicks;

        static const Uint64 TICKS_PER_SECOND = SDL_GetPerformanceFrequency();
        elapsedSeconds = (delta / static_cast<float>(TICKS_PER_SECOND));

        return delta;
    }
};

#endif //SENGINE_CLOCK_H
