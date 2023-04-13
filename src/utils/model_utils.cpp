#include <iostream>
#include <filesystem>
#include <glad.h>

#include "assets/model.h"
#include "datatypes/texture.h"
#include "utils/model_utils.h"
#include "utils/file_util.h"

Model ObjToModel(const std::string &filePath) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);

    Texture *textures;
    std::filesystem::path path{ filePath };
    std::string pathDir = path.parent_path().string();
    for (int i = 0; i < scene->mNumMaterials; i++)
    {
        aiString aiPath;
        aiMaterial *aiMaterial = scene->mMaterials[i];
        if (aiMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aiPath, NULL, NULL, NULL, NULL, NULL) != AI_SUCCESS) continue;

        char *textureData;
        std::string texturePath = (pathDir + "/" + aiPath.data);
        std::cout << texturePath << std::endl;
        FileReadAllBytes(texturePath, textureData);

        Texture texture{ 1, textureData };
        textures[i] = texture;
    }

    SceneToModel(scene, textures);
}

Model SceneToModel(const aiScene *scene, Texture *textures) {
    Model model;
    Assimp::Importer importer;

    for (int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh *aiMesh = scene->mMeshes[i];
        std::vector<GLfloat> vertices, colours, texCoords;
        unsigned int totalVertices = aiMesh->mNumVertices;
        for (int o = 0; o < totalVertices; o++) {
            aiVector3D aiVertex = aiMesh->mVertices[o];
            vertices.push_back(static_cast<GLfloat>(aiVertex.x));
            vertices.push_back(static_cast<GLfloat>(aiVertex.y));
            vertices.push_back(static_cast<GLfloat>(aiVertex.z));

            aiColor4D *aiColour = aiMesh->mColors[o];
            colours.push_back(static_cast<GLfloat>(aiColour->r));
            colours.push_back(static_cast<GLfloat>(aiColour->g));
            colours.push_back(static_cast<GLfloat>(aiColour->b));

            aiVector3t<ai_real> *aiTexCoord = aiMesh->mTextureCoords[o];
            texCoords.push_back(static_cast<GLfloat>(aiTexCoord->x));
            texCoords.push_back(static_cast<GLfloat>(aiTexCoord->y));
            texCoords.push_back(static_cast<GLfloat>(aiTexCoord->z));
        }

        unsigned int materialIndex = aiMesh->mMaterialIndex;
        Texture texture = textures[materialIndex];
        Mesh mesh{ vertices, colours, texCoords, texture };
        model.AddMesh(mesh);
    }

    return model;
}