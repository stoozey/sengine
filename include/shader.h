#ifndef SENGINE_TEST1_SHADER_H
#define SENGINE_TEST1_SHADER_H

#include <string>

#include "glad/glad.h"

GLuint CompileShader(GLuint shaderType, const std::string &shaderSourceString) {
    if ((shaderType != GL_VERTEX_SHADER) && (shaderType != GL_FRAGMENT_SHADER)) return -1;

    GLuint shaderObject = glCreateShader(shaderType);
    const char *source = shaderSourceString.c_str();
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);

    return shaderObject;
}

GLuint CreateShaderProgram(const std::string &vertexShaderSource, const std::string &fragmentShaderSource) {
    GLuint programObject = glCreateProgram();
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);
    return programObject;
}

#endif //SENGINE_TEST1_SHADER_H
