#ifndef SENGINE_TEST1_SHADER_PROGRAM_DATA_H
#define SENGINE_TEST1_SHADER_PROGRAM_DATA_H

namespace structs {
    struct ShaderProgramData {
        char vertexShader[4096];
        char fragmentShader[4096];
        bool encoded = false;
    };
}

#endif //SENGINE_TEST1_SHADER_PROGRAM_DATA_H
