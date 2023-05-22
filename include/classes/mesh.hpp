#ifndef SENGINE_ASSET_CREATOR_MESH_HPP
#define SENGINE_ASSET_CREATOR_MESH_HPP

#include <vector>
#include <glad.h>
#include <utility>

#include "structs/vertex.hpp"
#include "assets/texture.hpp"
#include "assets/shader.hpp"

namespace classes {
    class Mesh {
    public:
        Mesh(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices, std::vector<std::shared_ptr<assets::Texture>> textures);
        ~Mesh();

        std::vector<structs::Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<std::shared_ptr<assets::Texture>> textures;

        void Draw(std::shared_ptr<assets::Shader> shader);
    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;

        void SetupMesh();
    };
}

#endif //SENGINE_ASSET_CREATOR_MESH_HPP
