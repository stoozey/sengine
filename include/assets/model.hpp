#ifndef SENGINE_TEST1_MODEL_H
#define SENGINE_TEST1_MODEL_H

#include <glm/glm.hpp>
#include <glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "assets/asset.hpp"
#include "structs/mesh.hpp"

namespace assets {
    class Model : public Asset {
    public:
        Model();

        static Model FromFile(const std::string &filePath);

        void Save(const std::string &filePath);
        void Load(const std::string &filePath);
    private:
        std::vector<structs::Mesh> meshes;
    };
}

#endif //SENGINE_TEST1_MODEL_H
