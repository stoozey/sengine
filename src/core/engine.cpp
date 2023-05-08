#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad.h>
#include <stb.h>
#include <assimp/Importer.hpp>
#include <spdlog/spdlog.h>
#include <nfd.h>

#include "core/engine.hpp"
#include "structs/clock.hpp"
#include "managers/input_manager.hpp"
#include "core/log.hpp"

core::Engine *g_Engine = new core::Engine();

namespace core {
    int WINDOW_WIDTH_DEFAULT = 1280;
    int WINDOW_HEIGHT_DEFAULT = 720;
    int FPS_DEFAULT = 60;

    Engine::Engine() {
        renderer = nullptr;
        window = nullptr;
        glContext = nullptr;

        loopRunning = false;

        fps = 0;
        cycleTime = 0.0f;
        SetFps(FPS_DEFAULT);

        windowWidth = WINDOW_WIDTH_DEFAULT;
        windowHeight = WINDOW_HEIGHT_DEFAULT;
    }

    Engine::~Engine() {
        if (window != nullptr) {
            SDL_DestroyWindow(window);
        }

        NFD_Quit();
        SDL_Quit();
    }

    void Engine::Initialize() {
        InitSdl();
        InitNfd();
    }

    void Engine::InitSdl() {
        SDL_CreateWindowAndRenderer(windowWidth, windowHeight, (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), &window, &renderer);
        if ((window == nullptr) || (renderer == nullptr)) core::Log::Critical("Engine::Initialize failed (window or renderer was null)");

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        glContext = SDL_GL_CreateContext(window);
        if (glContext == nullptr) core::Log::Critical("Engine::Initialize failed (glContext was null)");

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) core::Log::Critical("Engine::Initialize failed (glad wasn't initialized)");
    }

    void Engine::InitNfd() {
        if (NFD_Init() == NFD_OKAY) return;

        std::string error = NFD_GetError();
        core::Log::Critical("NFD failed to initialize: {}", error);
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

    int Engine::GetWindowWidth() {
        return windowWidth;
    }

    int Engine::GetWindowHeight() {
        return windowHeight;
    }

    std::shared_ptr<loopRunners::LoopRunner> Engine::GetLoopRunner(structs::LoopRunnerType loopRunnerType) {
        for (auto &loopRunner: loopRunners) {
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
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    loopRunning = false;
                    break;
                }
            }
        }

        for (auto &loopRunner: loopRunners)
            loopRunner->Update(deltaTime);
    }

    void Engine::Render() {
        for (auto &loopRunner: loopRunners)
            loopRunner->Render();
    }

    void Engine::RunLoop() {
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 last = 0;
        double deltaTime = 0.0;

        static structs::Clock systemClock;
        float accumulatedSeconds = 0.0f;

        loopRunning = true;
        while (loopRunning) {
            systemClock.Tick();
            accumulatedSeconds += systemClock.elapsedSeconds;

            if (std::isgreater(accumulatedSeconds, cycleTime)) {
                accumulatedSeconds = -cycleTime;

                // Update
                static structs::Clock physicsClock;
                physicsClock.Tick();

                last = now;
                now = SDL_GetPerformanceCounter();
                deltaTime = (
                        (static_cast<double>(now - last) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency())) *
                        0.01);
                //g_PhysicsManager.Update(cycleTime);

                g_InputManager->Poll();

                Update(deltaTime);

                // Render
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);

                glViewport(0, 0, windowWidth, windowHeight);
                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

                Render();
                SDL_GL_SwapWindow(window);
            }
        }
    }
}