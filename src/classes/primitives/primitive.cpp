#include "classes/primitives/primitive.hpp"
#include "assets/texture.hpp"

namespace classes {
    Primitive::Primitive(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices) : vertices(vertices), indices(indices) { }

    classes::Mesh Primitive::GenerateMesh() {
        std::vector<std::weak_ptr<assets::Texture>> textures;
        return { vertices, indices, textures };
    }
}