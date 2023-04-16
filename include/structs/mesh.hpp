#ifndef SENGINE_TEST1_MESH_H
#define SENGINE_TEST1_MESH_H

#include <memory>
#include <glad.h>
#include <iostream>

#include "structs/texture.hpp"

namespace structs {
    struct Mesh {
        ~Mesh() {
            std::cout << "destroying mesh" << std::endl;
        }

        std::vector<GLfloat> vertices;
        std::vector<GLfloat> colours;
        std::vector<GLfloat> texCoords;
        Texture texture;
    };
}

#endif //SENGINE_TEST1_MESH_H
