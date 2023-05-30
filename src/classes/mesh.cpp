#include <cstddef>
#include <utility>

#include "core/engine.hpp"
#include "structs/vertex.hpp"
#include "classes/mesh.hpp"
#include "assets/texture.hpp"
#include "utils/asset_util.hpp"

namespace classes {
    Mesh::Mesh(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices, std::vector<std::weak_ptr<assets::Texture>> textures)
        : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)), VAO(0), VBO(0), EBO(0) {
        SetupMesh();
    }

    Mesh::~Mesh() {
        core::Log::Info("deleting mesh");
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    void Mesh::SetupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        GLsizei vertexSize = sizeof(structs::Vertex);
        GLsizei verticesSize = static_cast<GLsizei>(vertices.size());
        glBufferData(GL_ARRAY_BUFFER, verticesSize * vertexSize, &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*) nullptr);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)offsetof(structs::Vertex, normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offsetof(structs::Vertex, texCoords));

        glBindVertexArray(0);
    }

    void Mesh::Draw() {
        for (int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding

            auto texture = textures[i];
            auto lock = utils::GetAssetLock<assets::Texture>(texture);
            glBindTexture(GL_TEXTURE_2D, lock->textureId);
        }

        glActiveTexture(GL_TEXTURE0);

        // draw mesh
        GLsizei indicesSize = static_cast<GLsizei>(indices.size());
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}
