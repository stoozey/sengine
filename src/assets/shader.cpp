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

    ShaderData encodedData;
    SDL_RWread(file, reinterpret_cast<char*>(&encodedData), sizeof(ShaderData), 1);
    SDL_RWclose(file);

    std::string vertexShader, fragmentShader;
    if (shaderData.encoded) {
        macaron::Base64::Decode(encodedData.vertexShader, vertexShader);
        macaron::Base64::Decode(encodedData.fragmentShader, fragmentShader);
    } else {
        vertexShader = encodedData.vertexShader;
        fragmentShader = encodedData.fragmentShader;
    }

    strcpy(shaderData.vertexShader, vertexShader.c_str());
    strcpy(shaderData.fragmentShader, fragmentShader.c_str());
    CreateProgram();
}

GLuint Shader::GetProgram() const {
    return program;
}

bool Shader::ProgramExists() const {
    return (program > 0);
}

UniformData Shader::GetUniformData(const std::string &name) {
    auto find = uniformData.find(name);
    if (find == uniformData.end()) throw std::invalid_argument(name);

    return find->second;
}

void Shader::SetUniform(const std::string &name, float value) {
    UniformData data = GetUniformData(name);
    glUniform1f(data.location, value);
}

void Shader::SetUniform(const std::string &name, glm::vec2 value) {
    UniformData data = GetUniformData(name);
    glUniform2f(data.location, value.x, value.y);
}

void Shader::SetUniform(const std::string &name, glm::vec3 value) {
    UniformData data = GetUniformData(name);
    glUniform3f(data.location, value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string &name, glm::vec4 value) {
    UniformData data = GetUniformData(name);
    glUniform4f(data.location, value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const std::string &name, glm::mat4 value) {
    UniformData data = GetUniformData(name);
    glUniformMatrix4fv(data.location, 1, GL_FALSE, &value[0][0]);
}

ShaderData Shader::GenerateEncodedShaderData() {
    std::string vertexEncoded = macaron::Base64::Encode(shaderData.vertexShader);
    std::string fragmentEncoded = macaron::Base64::Encode(shaderData.fragmentShader);

    ShaderData data{ "", "" };
    strcpy(data.vertexShader, vertexEncoded.c_str());
    strcpy(data.fragmentShader, fragmentEncoded.c_str());
    return data;
}

GLuint Shader::Compile(GLuint shaderType, const char *source) {
    //if ((shaderType != GL_VERTEX_SHADER) && (shaderType != GL_FRAGMENT_SHADER)) return -1;

    GLuint shaderObject = glCreateShader(shaderType);
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);

    return shaderObject;
}

void Shader::CreateProgram() {
    DeleteProgram();

    program = glCreateProgram();
    GLuint vertexShader = Compile(GL_VERTEX_SHADER, shaderData.vertexShader);
    GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, shaderData.fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glValidateProgram(program);

    FetchUniforms();
}

void Shader::DeleteProgram() {
    if (!ProgramExists()) return;

    glDeleteProgram(program);
    program = -1;

    uniformData.clear();
};

void Shader::FetchUniforms() {
    if (!ProgramExists()) return;

    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc)

    const GLsizei bufSize = 16; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);

    for (i = 0; i < count; i++)
    {
        glGetActiveUniform(program, (GLuint)i, bufSize, &length, &size, &type, name);

        GLint location = glGetUniformLocation(program, name);
        UniformData data{ type, location };
        uniformData.insert({name, data});

        std::cout << name << " " << type << std::endl;
    }
}