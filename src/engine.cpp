#include <typeinfo>
#include <cmath>
#include <iostream>
#include <fstream>

#include "engine.h"
#include "datatypes/clock.h"
#include "managers/input_manager.h"
#include "glad/glad.h"
#include "assets/shader.h"

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
    cycleTime = 0.0f;
    SetFps(FPS_DEFAULT);

    windowWidth = WINDOW_WIDTH_DEFAULT;
    windowHeight = WINDOW_HEIGHT_DEFAULT;
}

Engine::~Engine() {
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
}

void Engine::Initialize() {
    InitSdl();
    InitOpenGl();
}

void Engine::InitSdl() {
    SDL_CreateWindowAndRenderer(windowWidth, windowHeight, (SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL), &window, &renderer);
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

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
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

void Engine::AddLoopRunner(std::shared_ptr<LoopRunner> &loopRunner) {
    loopRunners.push_back(loopRunner);
}

std::shared_ptr<LoopRunner> Engine::GetLoopRunner(LoopRunnerType loopRunnerType) {
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


    /// TEMP

    // vb 1

    const std::vector<GLfloat> vertexPosition {
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f,
    };

    // poop
    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBufferObject = 0;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexPosition.size() * sizeof(GLfloat),
                 vertexPosition.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // vb 2
    const std::vector<GLfloat> vertexColour {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
    };

    GLuint vertexBufferObject2 = 1;
    glGenBuffers(1, &vertexBufferObject2);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject2);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexColour.size() * sizeof(GLfloat),
                 vertexColour.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          nullptr);

    // something!
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


    Shader shader = Shader();
    shader.Load("E:\\shader2.asset");

    /// TEMP

    std::cout << shader.shaderData.vertexShader << std::endl<< std::endl<< std::endl<< std::endl<< std::endl<< std::endl;
    std::cout << shader.shaderData.fragmentShader << std::endl<< std::endl<< std::endl<< std::endl<< std::endl<< std::endl;

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
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);

            glViewport(0, 0, windowWidth, windowHeight);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


            glUseProgram(shader.GetProgram());


            glBindVertexArray(vertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

            glDrawArrays(GL_TRIANGLES, 0, 3);


            Render();
            SDL_GL_SwapWindow(window);
        }
    }
}