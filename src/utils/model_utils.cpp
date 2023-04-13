#include <iostream>
#include <filesystem>
#include <glad.h>

#include "assets/model.h"
#include "datatypes/texture.h"
#include "utils/model_utils.h"
#include "utils/file_util.h"

const int CHANNEL_INDEX = 0;

Model ObjToModel(const std::string &filePath) {
    std::cout << "1" << std::endl;
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    std::cout << "2" << std::endl;
    std::vector<std::shared_ptr<Texture>> textures;
    std::filesystem::path path{ filePath };
    std::string pathDir = path.parent_path().string();
    for (int i = 0; i < scene->mNumMaterials; i++)
    {
        std::cout << "3" << std::endl;
        aiString aiPath;
        aiMaterial *aiMaterial = scene->mMaterials[i];
        if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
        {
            std::cout << "4" << std::endl;
            char *textureData;
            std::string texturePath = (pathDir + "/" + aiPath.data);
            std::cout << texturePath << std::endl;
            size_t textureDataSize = FileReadAllBytes(texturePath, &textureData);

            std::cout << "5 " << textureDataSize << std::endl;
            std::shared_ptr<Texture> texture = std::make_shared<Texture>(GL_TEXTURE_2D, textureDataSize, textureData);
            textures.push_back(texture);
        }
//        } else {
//            std::cout << "5 penis" << std::endl;
//            Texture texture{ GL_TEXTURE_2D, 0, nullptr };
//            textures.push_back(texture);
//        }
    }

    std::cout << "6" << std::endl;
    return SceneToModel(scene, textures);
}

Model SceneToModel(const aiScene *scene, const std::vector<std::shared_ptr<Texture>> &textures) {
    std::cout << "s1" << std::endl;
    Model model;
    Assimp::Importer importer;
    std::cout << "s2" << std::endl;
    for (int i = 0; i < scene->mNumMeshes; i++) {
        std::cout << "s3." << i << std::endl;
        aiMesh *aiMesh = scene->mMeshes[i];
        std::vector<GLfloat> vertices, colours, texCoords;
        std::cout << "s3" << std::endl;
        bool hasColour = aiMesh->HasVertexColors(CHANNEL_INDEX);
        bool hasTexCoords = aiMesh->HasTextureCoords(CHANNEL_INDEX);
        std::cout << "s4" << std::endl;
        unsigned int totalVertices = aiMesh->mNumVertices;
        for (int o = 0; o < totalVertices; o++) {
            aiVector3D aiVertex = aiMesh->mVertices[o];
            vertices.push_back(static_cast<GLfloat>(aiVertex.x));
            vertices.push_back(static_cast<GLfloat>(aiVertex.y));
            vertices.push_back(static_cast<GLfloat>(aiVertex.z));

            if (hasColour) {
                aiColor4t<ai_real> aiColour = aiMesh->mColors[CHANNEL_INDEX][o];
                colours.push_back(static_cast<GLfloat>(aiColour.r));
                colours.push_back(static_cast<GLfloat>(aiColour.g));
                colours.push_back(static_cast<GLfloat>(aiColour.b));
            }

            if (hasTexCoords) {
                aiVector3t<ai_real> aiTexCoord = aiMesh->mTextureCoords[CHANNEL_INDEX][o];
                texCoords.push_back(static_cast<GLfloat>(aiTexCoord.x));
                texCoords.push_back(static_cast<GLfloat>(aiTexCoord.y));
                texCoords.push_back(static_cast<GLfloat>(0.0f));
            }
        }
        std::cout << "s6" << std::endl;
        unsigned int materialIndex = aiMesh->mMaterialIndex;
        std::cout << scene->mNumMaterials << " PGFUJWSOIURGHESDIOR " << materialIndex << " giggity miggidy" << std::endl;
        const std::shared_ptr<Texture> &texture = textures[materialIndex];
        std::cout << vertices.size() << " " << colours.size() << " " << texCoords.size() << " " << texture->textureDataSize << std::endl;
        Mesh mesh{ vertices, colours, texCoords, texture };
        model.meshes.push_back(mesh);
        std::cout << "s6.5" << std::endl;
    }
    std::cout << "s7" << std::endl;
    return model;
}