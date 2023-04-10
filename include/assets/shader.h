#ifndef SENGINE_TEST1_SHADER_H
#define SENGINE_TEST1_SHADER_H

#include "assets/asset.h"
#include "glad/glad.h"

struct ShaderData {
    char vertexShader[4096];
    char fragmentShader[4096];
    bool encoded = false;
};

class Shader : public Asset {
public:

    Shader();
    void Save(const std::string& filePath) override;
    void Load(const std::string& filePath) override;

    GLuint GetProgram() const;

    ShaderData shaderData;
private:
    static AssetInfo assetInfo;
    static GLuint Compile(GLuint shaderType, const char *source);

    ShaderData GenerateEncodedShaderData();

    GLuint program;
    void CreateProgram();
};

#endif //SENGINE_TEST1_SHADER_H
