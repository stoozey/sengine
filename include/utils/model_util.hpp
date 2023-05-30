#ifndef SENGINE_TEST1_MODEL_UTIL_H
#define SENGINE_TEST1_MODEL_UTIL_H

#include <vector>

#include "assets/model.hpp"
#include "classes/mesh.hpp"

namespace utils {
    void ObjToModel(const std::string &filePath, assets::Model *out);

    void SceneToModel(const aiScene *scene, assets::Model *out);

    void SceneToMeshVector(const aiScene *scene, std::vector<classes::Mesh> *outMeshes);
}

#endif //SENGINE_TEST1_MODEL_UTIL_H
