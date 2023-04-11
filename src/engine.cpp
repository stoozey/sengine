#include <typeinfo>
#include <cmath>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "engine.h"
#include "datatypes/clock.h"
#include "managers/input_manager.h"
#include "glad/glad.h"
#include "stb/stb.h"
#include "assets/shader.h"

int WINDOW_WIDTH_DEFAULT = 1280;
int WINDOW_HEIGHT_DEFAULT = 720;
int FPS_DEFAULT = 60;

static void GlClearAllErrors() {
    while (glGetError() != GL_NO_ERROR) {

    }
}

static bool GlCheckErrorStatus(const char *functionName, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "OPENGL ERROR: " << error << " occurred on " << line <<  ":" << functionName << std::endl;
        return true;
    }

    return false;
}

#define GlCheck(x) GlClearAllErrors(); x; GlCheckErrorStatus(#x, __LINE__);

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

    const std::vector<GLfloat> vertexData{
            // 0
            -0.5f, -0.5f, 0.0f, // left
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f,
            // 1
            0.5f, -0.5f, 0.0f, // right
            0.0f, 1.0f, 0.0f,
            1.0f, 0.0f,
            // 2
            -0.5f, 0.5f, 0.0f, // top left
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f,
            // 3
            0.5f, 0.5f, 0.0f, // top right
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f,
    };

    GLuint vertexArrayObject = 0;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBufferObject = 0;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 vertexData.size() * sizeof(GLfloat),
                 vertexData.data(),
                 GL_STATIC_DRAW);

    // setup ibo
    const std::vector<GLuint> indexBufferData {
        2, 0, 1,
        3, 2, 1
    };

    GLuint indexBufferObject = 0;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indexBufferData.size() * sizeof(GLuint),
                 indexBufferData.data(),
                 GL_STATIC_DRAW);

    // xyz
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          (sizeof(GLfloat) * 8),
                          (void*) 0);

    // rgb
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          (sizeof(GLfloat) * 8),
                          (GLvoid*) (sizeof(GLfloat) * 3));

    // texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          (sizeof(GLfloat) * 8),
                          (GLvoid*) (sizeof(GLfloat) * 6));

    // something!
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

    glm::vec3 uOffset{ 0.0f, 0.0f, -1.0f };

    Shader shader = Shader();
    shader.Load("E:\\shader2.asset");


    float totalTime = 0.0f;

    glm::mat4 perspective = glm::perspective(glm::radians(90.0f), (float) windowWidth / (float) windowHeight, 0.1f, 30.0f);

    int imageWidth, imageHeight, channelsCount;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *bytes = stbi_load(R"(C:\Users\Jo\Pictures\alex worm.png)", &imageWidth, &imageHeight, &channelsCount, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE0, 0);

    /// TEMP

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


            glBindVertexArray(vertexArrayObject);
            glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
            glBindTexture(GL_TEXTURE_2D, texture);

            glUseProgram(shader.GetProgram());
            glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), uOffset) * glm::rotate(glm::mat4(1.0f), glm::radians((totalTime / 10) * 360), glm::vec3(0.0f, 1.0f, 0.0f));
            shader.SetUniform("u_modelMatrix", modelMatrix);
            shader.SetUniform("u_projection", perspective);

            GlCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));



            float s = sin(totalTime);
            totalTime += deltaTime;

            //uOffset.z += s;



            Render();
            SDL_GL_SwapWindow(window);
        }
    }
}