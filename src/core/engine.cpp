#include <cmath>
#include <iostream>
#include <glad.h>
#include <stb.h>
#include <spdlog/spdlog.h>
#include <nfd.h>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "core/engine.hpp"
#include "structs/clock.hpp"
#include "managers/input_manager.hpp"
#include "core/log.hpp"
#include "assets/shader.hpp"
#include "managers/asset_manager.hpp"

std::unique_ptr<core::Engine> g_Engine = std::make_unique<core::Engine>();

namespace core {
    const int WINDOW_WIDTH_DEFAULT = 1280;
    const int WINDOW_HEIGHT_DEFAULT = 720;
    const int FPS_DEFAULT = 60;

    Engine::Engine() {
        renderer = nullptr;
        window = nullptr;
        glContext = nullptr;
        io = nullptr;

        loopRunning = false;

        fps = 0;
        cycleTime = 0.0f;
        SetFps(FPS_DEFAULT);

        windowWidth = WINDOW_WIDTH_DEFAULT;
        windowHeight = WINDOW_HEIGHT_DEFAULT;

        clearColour = { 0.5f, 0.5f, 0.5f, 0.5f };
    }

    Engine::~Engine() {
        StopLoop();
        Free();
    }

    void Engine::Free() {
        if (window != nullptr) {
            SDL_DestroyWindow(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        NFD_Quit();
        SDL_Quit();
    }

#pragma region init

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

    void Engine::InitNfd() { // NOLINT(readability-convert-member-functions-to-static)
        if (NFD_Init() == NFD_OKAY) return;

        std::string error = NFD_GetError();
        core::Log::Critical("NFD failed to initialize: {}", error);
    }

    void Engine::InitImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        io = &ImGui::GetIO(); (void)io;
        io->ConfigFlags |= (ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad);

        ImGui::StyleColorsLight();

        ImGui_ImplSDL2_InitForOpenGL(window, glContext);
        ImGui_ImplOpenGL3_Init(assets::Shader::glslVersion);
    }

    void Engine::Initialize() {
        InitSdl();
        InitNfd();
        InitImGui();
    }

#pragma endregion

#pragma region getters

    SDL_Renderer *Engine::GetRenderer() {
        return renderer;
    }

    SDL_Window *Engine::GetWindow() {
        return window;
    }

    SDL_GLContext *Engine::GetGlContext() {
        return &glContext;
    }

    ImGuiIO *Engine::GetImGuiIo() {
        return io;
    }

    int Engine::GetWindowWidth() const {
        return windowWidth;
    }

    int Engine::GetWindowHeight() const {
        return windowHeight;
    }

#pragma endregion

#pragma region setters

    void Engine::SetClearColour(const structs::Colour &colour) {
        clearColour = colour;
    }

    void Engine::SetFps(int targetFps) {
        fps = targetFps;
        cycleTime = (1.0f / static_cast<float>(fps));
    }

#pragma endregion

#pragma region loop

    void Engine::Update(double deltaTime) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch (event.type) {
                case SDL_QUIT: {
                    loopRunning = false;
                    break;
                }
            }
        }

        for (const auto &pair : loopRunners) {
            const auto &loopRunner = pair.second;
            loopRunner->Update(deltaTime);
        }
    }

    void Engine::Render() {
        for (const auto &pair : loopRunners) {
            const auto &loopRunner = pair.second;
            loopRunner->Render();
        }
    }

    void Engine::RunLoop() {
        try {
            // setup performance tracking
            Uint64 now = SDL_GetPerformanceCounter();
            Uint64 last = 0;
            double deltaTime = 0.0;

            static structs::Clock systemClock;
            float accumulatedSeconds = 0.0f;

            // run loop
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
                    //g_PhysicsManager.Update(deltaTime);

                    auto inputManager = GetManager<managers::InputManager>();
                    if (inputManager != nullptr) {
                        inputManager->Poll();
                    }

                    Update(deltaTime);

                    // Render
                    glDisable(GL_DEPTH_TEST);
                    glDisable(GL_CULL_FACE);

                    glViewport(0, 0, windowWidth, windowHeight);
                    glClearColor(clearColour.r, clearColour.g, clearColour.b, clearColour.a);
                    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

                    // setup imgui frame
                    ImGui_ImplOpenGL3_NewFrame();
                    ImGui_ImplSDL2_NewFrame(window);
                    ImGui::NewFrame();

                    Render();

                    ImGui::Render();
                    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                    SDL_GL_SwapWindow(window);
                }
            }
        } catch (const char *e) {
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SEngine Error Occurred", e, window);
            exit(1);
        }
    }

    void Engine::StopLoop() {
        loopRunning = false;
    }

#pragma endregion
}