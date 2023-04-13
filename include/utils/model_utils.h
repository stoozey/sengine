#ifndef SENGINE_TEST1_MODEL_UTILS_H
#define SENGINE_TEST1_MODEL_UTILS_H

#include "assets/model.h"

Model ObjToModel(const std::string &filePath);

Model SceneToModel(const aiScene *scene, Texture *textures);

#endif //SENGINE_TEST1_MODEL_UTILS_H
