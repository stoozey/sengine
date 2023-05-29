//#include <cstddef>
//#include <utility>
//
//#include "structs/vertex.hpp"
//#include "classes/mesh.hpp"
//#include "assets/texture.hpp"
//
//namespace classes {
//    Mesh::Mesh(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices, std::vector<std::weak_ptr<assets::Texture>> textures)
//        : vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures)), VAO(0), VBO(0), EBO(0) {
//        SetupMesh();
//    }
//
//    Mesh::~Mesh() {
//        core::Log::Info("deleting mesh");
//        glDeleteVertexArrays(1, &VAO);
//        glDeleteBuffers(1, &VBO);
//        glDeleteBuffers(1, &EBO);
//    }
//
//    void Mesh::SetupMesh() {
//        glGenVertexArrays(1, &VAO);
//        glGenBuffers(1, &VBO);
//        glGenBuffers(1, &EBO);
//
//        glBindVertexArray(VAO);
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//        size_t vertexSize = sizeof(structs::Vertex);
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * vertexSize, &vertices[0], GL_STATIC_DRAW);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
//                     &indices[0], GL_STATIC_DRAW);
//
//        // vertex positions
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*) nullptr);
//        // vertex normals
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)offsetof(structs::Vertex, normal));
//        // vertex texture coords
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offsetof(structs::Vertex, texCoords));
//
//        glBindVertexArray(0);
//    }
//
//    void Mesh::Draw(std::weak_ptr<assets::Shader> shader) {
//        unsigned int diffuseNr = 1;
//        unsigned int specularNr = 1;
//        for (int i = 0; i < textures.size(); i++)
//        {
//            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
//            // retrieve texture number (the N in diffuse_textureN)
////            std::string number;
////            std::string name = textures[i].type;
////            if(name == "texture_diffuse")
////                number = std::to_string(diffuseNr++);
////            else if(name == "texture_specular")
////                number = std::to_string(specularNr++);
//
//            std::string name = "u_textureDiffuse";
//            std::string number = std::to_string(diffuseNr++);
//
//
//            shader->SetUniform(name + number, i);
//
//            auto texture = textures[i];
//            if (auto lock = texture.lock()) {
//                glBindTexture(GL_TEXTURE_2D, lock->textureId);
//            } else {
//
//            }
//        }
//        glActiveTexture(GL_TEXTURE0);
//
//        // draw mesh
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//    }
//}
