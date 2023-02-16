#include <typeinfo>
#include <cmath>
#include <iostream>

#include "engine.h"
#include "datatypes/clock.h"

int WINDOW_WIDTH_DEFAULT = 1280;
int WINDOW_HEIGHT_DEFAULT = 720;
int FPS_DEFAULT = 60;

Engine *g_Engine = new Engine();

void Engine::Initialize() {
    SetFps(FPS_DEFAULT);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH_DEFAULT, WINDOW_HEIGHT_DEFAULT, SDL_WINDOW_SHOWN, &window, &renderer);
    loopRunning = true;
}

SDL_Renderer *Engine::GetRenderer() {
    return renderer;
}

SDL_Window *Engine::GetWindow() {
    return window;
}

void Engine::AddLoopRunner(LoopRunner *loopRunner) {
    loopRunners.push_back(loopRunner);
}

template<typename T>
T *Engine::GetLoopRunner() {
    for (auto &loopRunner : loopRunners) {
        if (typeid(loopRunner) == typeid(T)) {
            return loopRunner;
        }
    }

    return nullptr;
}

void Engine::SetFps(int targetFps) {
    fps = targetFps;
    cycleTime = (1.0f / fps);
}

void Engine::Update(double deltaTime) {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                loopRunning = false;
                break;
            }
        }
    }

    for (auto &loopRunner : loopRunners)
        loopRunner->Update(deltaTime);
}

void Engine::Render() {
    for (auto &loopRunner : loopRunners)
        loopRunner->Render();
}

void Engine::RunLoop() {
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    double deltaTime = 0;

    static Clock systemClock;
    float accumulatedSeconds = 0.0f;

    while (loopRunning)
    {
        systemClock.Tick();
        accumulatedSeconds += systemClock.elapsedSeconds;

        if (std::isgreater(accumulatedSeconds, cycleTime))
        {
            accumulatedSeconds = -cycleTime;

            // Update
            static Clock physicsClock;
            physicsClock.Tick();

            last = now;
            now = SDL_GetPerformanceCounter();
            deltaTime = ((double) ((now - last) * 1000 / (double) SDL_GetPerformanceFrequency()) * 0.01);
            //g_PhysicsManager.Update(cycleTime);

            //InputManager::Poll();
            Update(deltaTime);

            // Render
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            Render();
            SDL_RenderPresent(renderer);
        }
    }
}