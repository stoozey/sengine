#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <list>
#include <memory>
#include <imgui.h>
#include <utility>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

#include "loop_runners/loop_runner.hpp"
#include "loop_runners/entity_loop_runner.hpp"
#include "structs/loop_runners/loop_runner_type.hpp"
#include "structs/colour.hpp"
#include "managers/manager.hpp"

namespace core {
    class Engine {
    public:
        Engine();
        ~Engine();

        void Initialize();

        SDL_Renderer *GetRenderer();
        SDL_Window *GetWindow();
        SDL_GLContext *GetGlContext();
        ImGuiIO *GetImGuiIo();

        template<typename T>
        T *AddLoopRunner();

        template<typename T>
        T *GetLoopRunner();

        template<typename T>
        T *AddManager();

        template<typename T>
        T *GetManager();

        void SetFps(int targetFps);
        void Update(double deltaTime);
        void Render();
        void RunLoop();
        void StopLoop();

        int GetWindowWidth() const;
        int GetWindowHeight() const;

        void SetClearColour(const structs::Colour &colour);
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_GLContext glContext;
        ImGuiIO *io;

        std::unordered_map<std::type_index, std::unique_ptr<loopRunners::LoopRunner>> loopRunners;
        std::unordered_map<std::type_index, std::unique_ptr<managers::Manager>> managers;

        bool loopRunning;

        int fps;
        float cycleTime;

        int windowWidth;
        int windowHeight;

        structs::Colour clearColour;

        void InitSdl();
        void InitNfd();
        void InitImGui();

        void Free();
    };
}

#include "engine.tpp"
extern std::unique_ptr<core::Engine> g_Engine;
#endif //SENGINE_ENGINE_H
