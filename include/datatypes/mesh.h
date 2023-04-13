#ifndef SENGINE_TEST1_MESH_H
#define SENGINE_TEST1_MESH_H

#include <memory>

#include "datatypes/texture.h"

struct Mesh {
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colours;
    std::vector<GLfloat> texCoords;
    Texture texture;
};

#endif //SENGINE_TEST1_MESH_H
