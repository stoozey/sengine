#ifndef SENGINE_TEST1_SHADER_PROGRAM_DATA_H
#define SENGINE_TEST1_SHADER_PROGRAM_DATA_H

#include "assets/shader.hpp"

const size_t SHADER_PROGRAM_SIZE = 4096;

namespace structs {
    struct ShaderProgramData {
        char vertexShader[SHADER_PROGRAM_SIZE];
        char fragmentShader[SHADER_PROGRAM_SIZE];
        bool encoded = true;
    };
}

#endif //SENGINE_TEST1_SHADER_PROGRAM_DATA_H
