#ifndef SENGINE_ENGINE_H
#define SENGINE_ENGINE_H

#include <SDL.h>
#include <list>

#include "loop_runners/loop_runner.h"

class Engine {
public:
    Engine();
    ~Engine();

    void Initialize();

    SDL_Renderer *GetRenderer();
    SDL_Window *GetWindow();
    SDL_GLContext *GetGlContext();

    LoopRunner *GetLoopRunner(LoopRunnerType loopRunnerType);
    void AddLoopRunner(LoopRunner *loopRunner);

    void SetFps(int targetFps);


    void Update(double deltaTime);
    void Render();
    void RunLoop();
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_GLContext glContext;

    std::list<LoopRunner*> loopRunners;

    bool loopRunning;

    int fps;
    float cycleTime;
};

extern Engine *g_Engine;

#endif //SENGINE_ENGINE_H
