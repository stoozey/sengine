#ifndef SENGINE_TEST1_SHADER_H
#define SENGINE_TEST1_SHADER_H

#include <glm/glm.hpp>
#include <map>
#include <glad.h>

#include "assets/asset.hpp"
#include "structs/shaders/shader_program_data.hpp"
#include "structs/shaders/shader_uniform_data.hpp"

namespace assets {
    class Shader : public Asset {
    public:
        Shader();
        ~Shader();

        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;

        GLuint GetProgram() const;
        bool ProgramExists() const;

        void SetUniform(const std::string &name, float value);
        void SetUniform(const std::string &name, glm::vec2 value);
        void SetUniform(const std::string &name, glm::vec3 value);
        void SetUniform(const std::string &name, glm::vec4 value);
        void SetUniform(const std::string &name, glm::mat4 value);

        static const char *glslVersion;

        structs::ShaderProgramData programData;
    private:
        static GLuint Compile(GLuint shaderType, const char *source);

        structs::ShaderProgramData GenerateEncodedShaderData();
        structs::ShaderUniformData GetUniformData(const std::string &name);

        void CreateProgram();
        void DeleteProgram();
        void FetchUniforms();

        GLuint program;
        std::map<std::string, structs::ShaderUniformData> uniformData;
    };
}

#endif //SENGINE_TEST1_SHADER_H
