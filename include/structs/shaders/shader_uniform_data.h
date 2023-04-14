#ifndef SENGINE_TEST1_SHADER_UNIFORM_DATA_H
#define SENGINE_TEST1_SHADER_UNIFORM_DATA_H

#include <glad.h>

namespace structs {
    struct ShaderUniformData {
        GLuint type;
        GLint location;
    };
}

#endif //SENGINE_TEST1_SHADER_UNIFORM_DATA_H
