#include <typeinfo>
#include <cmath>
#include <iostream>

#include "glad/glad.h"
#include "engine.h"
#include "datatypes/clock.h"
#include "managers/input_manager.h"

int WINDOW_WIDTH_DEFAULT = 1280;
int WINDOW_HEIGHT_DEFAULT = 720;
int FPS_DEFAULT = 60;

Engine *g_Engine = new Engine();

Engine::Engine() {
    renderer = nullptr;
    window = nullptr;
    glContext = nullptr;

    loopRunning = false;

    fps = 0;
    cycleTime = 0;
    SetFps(FPS_DEFAULT);
}

Engine::~Engine() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void Engine::Initialize() {
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH_DEFAULT, WINDOW_HEIGHT_DEFAULT, (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), &window, &renderer);
    if ((window == nullptr) || (renderer == nullptr)) {
        std::cout << "Engine::Initialize failed (window or renderer was null)" << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cout << "Engine::Initialize failed (glContext was null)" << std::endl;
        exit(1);
    }
}

SDL_Renderer *Engine::GetRenderer() {
    return renderer;
}

SDL_Window *Engine::GetWindow() {
    return window;
}

SDL_GLContext *Engine::GetGlContext() {
    return &glContext;
}

void Engine::AddLoopRunner(LoopRunner *loopRunner) {
    loopRunners.push_back(loopRunner);
}

LoopRunner *Engine::GetLoopRunner(LoopRunnerType loopRunnerType) {
    for (auto &loopRunner : loopRunners) {
        if (loopRunner->GetLoopRunnerType() == loopRunnerType) return loopRunner;
    }

    return nullptr;
}

void Engine::SetFps(int targetFps) {
    fps = targetFps;
    cycleTime = (1.0f / static_cast<float>(fps));
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
    double deltaTime = 0.0;

    static Clock systemClock;
    float accumulatedSeconds = 0.0f;

    loopRunning = true;
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
            deltaTime = ((static_cast<double>(now - last) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency())) * 0.01);
            //g_PhysicsManager.Update(cycleTime);

            g_InputManager->Poll();
            Update(deltaTime);

            // Render
            Render();
            SDL_GL_SwapWindow(window);
        }
    }
}