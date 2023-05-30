#ifndef SENGINE_ASSET_CREATOR_PRIMITIVE_HPP
#define SENGINE_ASSET_CREATOR_PRIMITIVE_HPP

#include <vector>
#include <glad.h>

#include "structs/vertex.hpp"
#include "classes/mesh.hpp"
#include "structs/primitive_type.hpp"

namespace classes {
    class Primitive {
    public:
        static classes::Mesh GetMesh(const structs::PrimitiveType &primitiveType);
        classes::Mesh GenerateMesh();
    private:
        Primitive(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices);

        std::vector<structs::Vertex> vertices;
        std::vector<GLuint> indices;
    };
}

#endif //SENGINE_ASSET_CREATOR_PRIMITIVE_HPP
