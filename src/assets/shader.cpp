#include <iostream>

#include "assets/shader.h"
#include "base64/base64.h"

AssetInfo Shader::assetInfo{ AssetType::Shader };

Shader::Shader() {
    shaderData = { "", "" };
    program = -1;
}

void Shader::Save(const std::string &filePath) {
    SDL_RWops *file = SDL_RWFromFile(filePath.c_str(), "w");
    WriteAssetInfo(file, assetInfo);

    ShaderData data = ((shaderData.encoded) ? GenerateEncodedShaderData() : shaderData);
    SDL_RWwrite(file, reinterpret_cast<char*>(&data), sizeof(ShaderData), 1);
    SDL_RWclose(file);
}

void Shader::Load(const std::string &filePath) {
    SDL_RWops *file = SDL_RWFromFile(filePath.c_str(), "r");
    ReadAssetInfo(file);

    ShaderData encodedData{ "", "" };
    SDL_RWread(file, reinterpret_cast<char*>(&encodedData), sizeof(ShaderData), 1);
    SDL_RWclose(file);

    std::string vertexShader, fragmentShader;
    if (shaderData.encoded) {
        macaron::Base64::Decode(encodedData.vertexShader, vertexShader);
        macaron::Base64::Decode(encodedData.fragmentShader, fragmentShader);
    } else {
        vertexShader = encodedData.vertexShader;
        fragmentShader = encodedData.vertexShader;
    }

    strcpy(shaderData.vertexShader, vertexShader.c_str());
    strcpy(shaderData.fragmentShader, fragmentShader.c_str());
    CreateProgram();
}

ShaderData Shader::GenerateEncodedShaderData() {
    std::string vertexEncoded = macaron::Base64::Encode(shaderData.vertexShader);
    std::string fragmentEncoded = macaron::Base64::Encode(shaderData.fragmentShader);

    ShaderData data{ "", "" };
    strcpy(data.vertexShader, vertexEncoded.c_str());
    strcpy(data.fragmentShader, fragmentEncoded.c_str());
    return data;
}

GLuint Shader::GetProgram() const {
    return program;
}

GLuint Shader::Compile(GLuint shaderType, const char *source) {
    //if ((shaderType != GL_VERTEX_SHADER) && (shaderType != GL_FRAGMENT_SHADER)) return -1;

    GLuint shaderObject = glCreateShader(shaderType);
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);

    return shaderObject;
}

void Shader::CreateProgram() {
    if (program > 0) {
        glDeleteProgram(program);
    }

    program = glCreateProgram();
    GLuint vertexShader = Compile(GL_VERTEX_SHADER, shaderData.vertexShader);
    GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, shaderData.fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glValidateProgram(program);
}