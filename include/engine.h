#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <map>

#include "loop_runners/loop_runner.h"

class SEngine {
public:
    SEngine();

private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};

extern SEngine g_SEngine;

#endif //SENGINE_ENGINE_H
