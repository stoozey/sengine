#ifndef SENGINE_ASSET_CREATOR_VERTEX_HPP
#define SENGINE_ASSET_CREATOR_VERTEX_HPP

#include <glm/glm.hpp>

namespace structs {
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };
}

#endif //SENGINE_ASSET_CREATOR_VERTEX_HPP
