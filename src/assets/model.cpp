#include <fstream>
#include <iostream>
#include <glad.h>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/postprocess.h>

#include "core/log.hpp"
#include "assets/model.hpp"
#include "structs/vertex.hpp"

namespace assets {
    Model::Model() : Asset(structs::AssetType::Model), scene(nullptr) {
        core::Log::Error("poop!");
    }

    void Model::Load(const std::string &filePath) {
        Assimp::Importer importer;
        scene = importer.ReadFile(filePath, 0);
    }

    void Model::Save(const std::string &filePath) {
        core::Log::Info("saving");
        Assimp::Exporter exporter;
        Assimp::ExportProperties *exportProperties = new Assimp::ExportProperties;
        const aiExportDataBlob *blob = exporter.ExportToBlob(scene, "ASSBIN", 0u, exportProperties);
        delete exportProperties;
        if (blob == nullptr) core::Log::Error("failed to export blob for \"{}\"", filePath);

        core::Log::Info(std::to_string(blob->size));

        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
        file.write(reinterpret_cast<const char *>(&blob->data), blob->size);
        file.close();
        exporter.FreeBlob();
    }

    void Model::LoadFromFile(const std::string &filePath) {
        core::Log::Info("LoadFromFile1");
        Assimp::Importer importer;
        scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);
        core::Log::Info("LoadFromFile2");
        if ((!scene) || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)) core::Log::Error("model assimp error: {}", importer.GetErrorString());
        core::Log::Info("LoadFromFile3");
        std::string directory = filePath.substr(0, filePath.find_last_of('/'));
        ProcessNode(directory, scene->mRootNode);
        core::Log::Info("LoadFromFile4");
    }

//    std::vector<std::shared_ptr<assets::Texture>> LoadMaterialTextures(aiMaterial *mat, aiTextureType type,  typeName)
//    {
//        vector<Texture> textures;
//        for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//        {
//            aiString str;
//            mat->GetTexture(type, i, &str);
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), directory);
//            texture.type = typeName;
//            texture.path = str;
//            textures.push_back(texture);
//        }
//        return textures;
//    }

    void Model::ProcessNode(const std::string &directory, aiNode *node) {
        core::Log::Info("ProcessNode1");
        for (int i = 0; i < node->mNumMeshes; i++) {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh));
        }

        core::Log::Info("ProcessNode2");
        for (int i = 0; i < node->mNumChildren; i++) {
            ProcessNode(directory, node->mChildren[i]);
        }
    }

    classes::Mesh Model::ProcessMesh(aiMesh *mesh) {
        // vertices
        core::Log::Info("ProcessMesh1");
        std::vector<structs::Vertex> vertices;
        for (int i = 0; i < mesh->mNumVertices; i++)
        {
            glm::vec3 position;
            position.x = mesh->mVertices[i].x;
            position.y = mesh->mVertices[i].y;
            position.z = mesh->mVertices[i].z;

            glm::vec3 normal;
            if (mesh->mNormals != nullptr) {
                normal.x = mesh->mNormals[i].x;
                normal.y = mesh->mNormals[i].y;
                normal.z = mesh->mNormals[i].z;
            }

            glm::vec2 texCoords;
            if (mesh->mTextureCoords[0]) {
                texCoords.x = mesh->mTextureCoords[0][i].x;
                texCoords.y = mesh->mTextureCoords[0][i].y;
            }

            vertices.push_back({ position, normal, texCoords });
        }

        // indices
        core::Log::Info("ProcessMesh2");
        std::vector<GLuint> indices;
        for (int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // textures
        core::Log::Info("ProcessMesh3");
        std::vector<std::shared_ptr<assets::Texture>> textures;
//        if (mesh->mMaterialIndex >= 0)
//        {
//            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//            vector<Texture> diffuseMaps = loadMaterialTextures(material,
//                                                               aiTextureType_DIFFUSE, "texture_diffuse");
//            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//            vector<Texture> specularMaps = loadMaterialTextures(material,
//                                                                aiTextureType_SPECULAR, "texture_specular");
//            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//        }

        core::Log::Info("ProcessMesh4");
        return classes::Mesh(vertices, indices, textures);
    }

    void Model::Draw(std::shared_ptr<assets::Shader> shader) {
        for (auto &mesh : meshes) {
            mesh.Draw(shader);
        }
    }
}