#ifndef SENGINE_TEST1_MODEL_UTIL_H
#define SENGINE_TEST1_MODEL_UTIL_H

#include <vector>

#include "assets/model.h"

namespace utils {
    void ObjToModel(const std::string &filePath, assets::Model &out);

    void SceneToModel(const aiScene *scene, const std::vector<structs::Texture> &textures, assets::Model &out);
}

#endif //SENGINE_TEST1_MODEL_UTIL_H
