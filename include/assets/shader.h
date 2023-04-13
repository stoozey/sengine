#ifndef SENGINE_TEST1_SHADER_H
#define SENGINE_TEST1_SHADER_H

#include <glm/glm.hpp>
#include <map>
#include <glad.h>

#include "assets/asset.h"

struct ShaderData {
    char vertexShader[4096];
    char fragmentShader[4096];
    bool encoded = false;
};

struct UniformData {
    GLuint type;
    GLint location;
};

class Shader : public Asset {
public:

    Shader();
    void Save(const std::string &filePath) override;
    void Load(const std::string &filePath) override;

    GLuint GetProgram() const;
    bool ProgramExists() const;

    void SetUniform(const std::string &name, float value);
    void SetUniform(const std::string &name, glm::vec2 value);
    void SetUniform(const std::string &name, glm::vec3 value);
    void SetUniform(const std::string &name, glm::vec4 value);
    void SetUniform(const std::string &name, glm::mat4 value);

    ShaderData shaderData;
private:
    static AssetInfo assetInfo;
    static GLuint Compile(GLuint shaderType, const char *source);

    ShaderData GenerateEncodedShaderData();

    std::map<std::string, UniformData> uniformData;
    UniformData GetUniformData(const std::string &name);

    GLuint program;
    void CreateProgram();
    void DeleteProgram();

    void FetchUniforms();
};

#endif //SENGINE_TEST1_SHADER_H
