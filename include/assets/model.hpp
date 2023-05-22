#ifndef SENGINE_TEST1_MODEL_H
#define SENGINE_TEST1_MODEL_H

#include <vector>
#include <utility>
#include <assimp/scene.h>

#include "classes/mesh.hpp"
#include "assets/shader.hpp"

namespace assets {
    class Model : public Asset {
    public:
        Model();

        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;
        void LoadFromFile(const std::string &filePath);

        void Draw(std::shared_ptr<assets::Shader> shader);
        void ProcessNode(const std::string &directory, aiNode *node);
        classes::Mesh ProcessMesh(aiMesh *mesh);
    private:
        std::vector<classes::Mesh> meshes;
        const aiScene *scene;
    };
}

#endif //SENGINE_TEST1_MODEL_H
