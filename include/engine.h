#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <map>

#include "loop_runners/loop_runner.h"

class Engine {
public:
    Engine();

    SDL_Renderer *GetRenderer();
    SDL_Window *GetWindow();
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};

extern Engine *g_Engine;

#endif //SENGINE_ENGINE_H
