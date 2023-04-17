#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <list>
#include <memory>

#include "loop_runners/loop_runner.hpp"
#include "loop_runners/entity_loop_runner.hpp"
#include "structs/loop_runners/loop_runner_type.hpp"

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

        void AddLoopRunner(std::shared_ptr<loopRunners::LoopRunner> &loopRunner);
        void SetFps(int targetFps);
        void Update(double deltaTime);
        void Render();
        void RunLoop();

        int GetWindowWidth();
        int GetWindowHeight();
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        SDL_GLContext glContext;

        std::list<std::shared_ptr<loopRunners::LoopRunner>> loopRunners;

        bool loopRunning;

        int fps;
        float cycleTime;

        int windowWidth;
        int windowHeight;

        void InitSdl();

        void InitOpenGl();
    };
}

extern core::Engine *g_Engine;

#endif //SENGINE_ENGINE_H
