#include "engine.h"

Engine *g_Engine = new Engine();

SDL_Renderer *Engine::GetRenderer() {
    return renderer;
}

SDL_Window *Engine::GetWindow() {
    return window;
}