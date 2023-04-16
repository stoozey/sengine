#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad.h>
#include <stb.h>
#include <assimp/Importer.hpp>

#include "core/engine.h"
#include "structs/clock.h"
#include "managers/input_manager.h"
#include "assets/shader.h"
#include "assets/texture.h"
#include "managers/asset_manager.h"

core::Engine *g_Engine = new core::Engine();

namespace core {
    int WINDOW_WIDTH_DEFAULT = 1280;
    int WINDOW_HEIGHT_DEFAULT = 720;
    int FPS_DEFAULT = 60;

    static void GlClearAllErrors() {
        while (glGetError() != GL_NO_ERROR)
        {

        }
    }

    static bool GlCheckErrorStatus(const char *functionName, int line) {
        while (GLenum error = glGetError())
        {
            std::cout << "OPENGL ERROR: " << error << " occurred at " << line << ":" << functionName << std::endl;
            return true;
        }

        return false;
    }

    #define GlCheck(x) GlClearAllErrors(); x; GlCheckErrorStatus(#x, __LINE__);


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
        if (window != nullptr)
        {
            SDL_DestroyWindow(window);
        }

        SDL_Quit();
    }

    void Engine::Initialize() {
        InitSdl();
        InitOpenGl();
    }

    void Engine::InitSdl() {
        SDL_CreateWindowAndRenderer(windowWidth, windowHeight, (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), &window,
                                    &renderer);
        if ((window == nullptr) || (renderer == nullptr))
        {
            std::cout << "Engine::Initialize failed (window or renderer was null)" << std::endl;
            exit(1);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

        glContext = SDL_GL_CreateContext(window);
        if (glContext == nullptr)
        {
            std::cout << "Engine::Initialize failed (glContext was null)" << std::endl;
            exit(1);
        }

        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            std::cout << "Engine::Initialize failed (glad wasn't initialized)" << std::endl;
            exit(1);
        }
    }

    void Engine::InitOpenGl() {
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

    void Engine::AddLoopRunner(std::shared_ptr<loopRunners::LoopRunner> &loopRunner) {
        loopRunners.push_back(loopRunner);
    }

    std::shared_ptr<loopRunners::LoopRunner> Engine::GetLoopRunner(structs::LoopRunnerType loopRunnerType) {
        for (auto &loopRunner: loopRunners)
        {
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
        while (loopRunning)
        {
            systemClock.Tick();
            accumulatedSeconds += systemClock.elapsedSeconds;

            if (std::isgreater(accumulatedSeconds, cycleTime))
            {
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

                std::cout << "updating" << std::endl;
                Update(deltaTime);

                // Render
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);

                glViewport(0, 0, windowWidth, windowHeight);
                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

                std::cout << "rendering" << std::endl;
                Render();
                SDL_GL_SwapWindow(window);
            }
        }
    }
}