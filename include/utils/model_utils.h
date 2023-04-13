#ifndef SENGINE_TEST1_MODEL_UTILS_H
#define SENGINE_TEST1_MODEL_UTILS_H

#include <vector>

#include "assets/model.h"

void ObjToModel(const std::string &filePath, Model &out);

void SceneToModel(const aiScene *scene, const std::vector<Texture> &textures, Model &out);

#endif //SENGINE_TEST1_MODEL_UTILS_H
