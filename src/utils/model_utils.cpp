#include <iostream>
#include <filesystem>
#include <glad.h>

#include "assets/model.hpp"
#include "structs/texture.hpp"
#include "utils/model_util.hpp"
#include "utils/file_util.hpp"

namespace utils {
    const int CHANNEL_INDEX = 0;

    void ObjToModel(const std::string &filePath, assets::Model &out) {
        std::cout << "1" << std::endl;
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate |
                                                           aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

        std::cout << "2" << std::endl;
        std::vector<structs::Texture> textures;
        std::filesystem::path path{filePath};
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
                size_t textureDataSize = utils::FileReadAllBytes(texturePath, &textureData);

                std::cout << "5 " << textureDataSize << std::endl;
                structs::Texture texture{GL_TEXTURE_2D, textureDataSize, textureData};
                textures.push_back(texture);
            } else
            {
                std::cout << "5 penis" << std::endl;
                structs::Texture texture{GL_TEXTURE_2D, 0, nullptr};
                textures.push_back(texture);
            }
        }

        std::cout << "6" << std::endl;
        utils::SceneToModel(scene, textures, out);
    }

    void SceneToModel(const aiScene *scene, const std::vector<structs::Texture> &textures, assets::Model &out) {
        std::cout << "s1" << std::endl;
        Assimp::Importer importer;
        std::cout << "s2" << std::endl;
        for (int i = 0; i < scene->mNumMeshes; i++)
        {
            std::cout << "s3." << i << std::endl;
            aiMesh *aiMesh = scene->mMeshes[i];
            std::vector<GLfloat> vertices, colours, texCoords;
            std::cout << "s3" << std::endl;
            bool hasColour = aiMesh->HasVertexColors(CHANNEL_INDEX);
            bool hasTexCoords = aiMesh->HasTextureCoords(CHANNEL_INDEX);
            std::cout << "s4" << std::endl;
            unsigned int totalVertices = aiMesh->mNumVertices;
            for (int o = 0; o < totalVertices; o++)
            {
                aiVector3D aiVertex = aiMesh->mVertices[o];
                vertices.push_back(static_cast<GLfloat>(aiVertex.x));
                vertices.push_back(static_cast<GLfloat>(aiVertex.y));
                vertices.push_back(static_cast<GLfloat>(aiVertex.z));

                if (hasColour)
                {
                    aiColor4t<ai_real> aiColour = aiMesh->mColors[CHANNEL_INDEX][o];
                    colours.push_back(static_cast<GLfloat>(aiColour.r));
                    colours.push_back(static_cast<GLfloat>(aiColour.g));
                    colours.push_back(static_cast<GLfloat>(aiColour.b));
                }

                if (hasTexCoords)
                {
                    aiVector3t<ai_real> aiTexCoord = aiMesh->mTextureCoords[CHANNEL_INDEX][o];
                    texCoords.push_back(static_cast<GLfloat>(aiTexCoord.x));
                    texCoords.push_back(static_cast<GLfloat>(aiTexCoord.y));
                    texCoords.push_back(static_cast<GLfloat>(aiTexCoord.z));
                }
            }
            std::cout << "s6" << std::endl;
            unsigned int materialIndex = aiMesh->mMaterialIndex;
            std::cout << scene->mNumMaterials << " PGFUJWSOIURGHESDIOR " << materialIndex << " giggity miggidy"
                      << std::endl;
            const structs::Texture &texture = textures.at(materialIndex);
            std::cout << vertices.size() << " " << colours.size() << " " << texCoords.size() << " t "
                      << texture.textureType << "," << texture.textureDataSize << std::endl;
            structs::Mesh mesh{vertices, colours, texCoords, texture};
            out.meshes.push_back(mesh);
            std::cout << "s6.5" << std::endl;
        }
        std::cout << "s7" << std::endl;
    }
}