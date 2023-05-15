#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <list>
#include <memory>
#include <imgui.h>

#include "loop_runners/loop_runner.hpp"
#include "loop_runners/entity_loop_runner.hpp"
#include "structs/loop_runners/loop_runner_type.hpp"
#include "structs/colour.hpp"

namespace core {
    class Engine {
    public:
        Engine();
        ~Engine();

        void Initialize();

        SDL_Renderer *GetRenderer();
        SDL_Window *GetWindow();
        SDL_GLContext *GetGlContext();

        std::shared_ptr<loopRunners::LoopRunner> GetLoopRunner(structs::LoopRunnerType loopRunnerType);

        template<typename T>
        void AddLoopRunner(std::shared_ptr<T> &loopRunner);

        void SetFps(int targetFps);
        void Update(double deltaTime);
        void Render();
        void RunLoop();

        int GetWindowWidth();
        int GetWindowHeight();

        ImGuiIO *GetImGuiIo();

        void SetClearColour(const structs::Colour &colour);
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_GLContext glContext;
        ImGuiIO *io;

        std::list<std::shared_ptr<loopRunners::LoopRunner>> loopRunners;

        bool loopRunning;

        int fps;
        float cycleTime;

        int windowWidth;
        int windowHeight;

        structs::Colour clearColour;

        void InitSdl();
        void InitNfd();
        void InitImGui();
    };
}

#include "engine.tpp"
extern core::Engine *g_Engine;
#endif //SENGINE_ENGINE_H
