#include <utility>

#include "classes/primitive.hpp"
#include "assets/texture.hpp"
#include "exceptions/not_implemented.hpp"

namespace classes {
    Primitive::Primitive(std::vector<structs::Vertex> vertices, std::vector<GLuint> indices) : vertices(std::move(vertices)), indices(std::move(indices)) { }

    classes::Mesh Primitive::GetMesh(const structs::PrimitiveType &primitiveType) {
        switch (primitiveType) {
            case structs::PrimitiveType::Plane: {
                static std::vector<structs::Vertex> vertices = {
                        {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }}, // left
                        {{ 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }}, // right
                        {{ -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }}, // top left
                        {{ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }}, // top left
                };

                static std::vector<GLuint> indices = {
                        2, 0, 1,
                        3, 2, 1
                };

                static Primitive plane = Primitive(vertices, indices);

                return plane.GenerateMesh();
            }

            default: {
                throw exceptions::NotImplemented("Primitive::GetMesh");
            }
        }
    }

    classes::Mesh Primitive::GenerateMesh() {
        return { vertices, indices, { } };
    }
}