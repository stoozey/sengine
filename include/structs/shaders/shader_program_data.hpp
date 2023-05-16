#ifndef SENGINE_TEST1_SHADER_PROGRAM_DATA_H
#define SENGINE_TEST1_SHADER_PROGRAM_DATA_H

#include "assets/shader.hpp"

namespace structs {
    struct ShaderProgramData {
        char vertexShader[4096];
        char fragmentShader[4096];
        bool encoded = true;
    };
}

#endif //SENGINE_TEST1_SHADER_PROGRAM_DATA_H
