#include "classes/primitives/plane.hpp"
#include "structs/vertex.hpp"

namespace classes {
    Plane::Plane() : Primitive(
            {
                {{ -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }}, // left
                {{ 0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f }}, // right
                {{ -0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f }}, // top left
                {{ 0.5f, 0.5f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }}, // top left
            },
            {
                2, 0, 1,
                3, 2, 1
            }) { }
}