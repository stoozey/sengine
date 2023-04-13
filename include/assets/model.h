#ifndef SENGINE_TEST1_MODEL_H
#define SENGINE_TEST1_MODEL_H

#include <glm/glm.hpp>
#include <glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "assets/asset.h"
#include "datatypes/mesh.h"

class Model : public Asset {
public:
    static Model FromFile(const std::string &filePath);

    void Save(const std::string &filePath);
    void Load(const std::string &filePath);

    std::vector<Mesh> meshes;
private:
    static AssetInfo assetInfo;
};

#endif //SENGINE_TEST1_MODEL_H
