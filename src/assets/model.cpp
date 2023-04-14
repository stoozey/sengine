#include <fstream>
#include <iostream>
#include <glad.h>

#include "assets/model.h"

namespace assets {
    structs::AssetInfo Model::assetInfo = structs::AssetInfo{ structs::AssetType::Model };

    void WriteGlFloatVector(std::fstream &file, std::vector<GLfloat> &inVector) {
        uint32_t size = inVector.size();
        std::cout << "writing size " << size << std::endl;
        file.write(reinterpret_cast<char *>(&size), sizeof(uint32_t));

        for (GLfloat value: inVector)
        {
            file.write(reinterpret_cast<char *>(&value), sizeof(GLfloat));
        }
    }

    void ReadGlFloatVector(std::fstream &file, std::vector<GLfloat> &outVector) {
        uint32_t size;
        file.read(reinterpret_cast<char *>(&size), sizeof(uint32_t));
        std::cout << "found size is " << size << std::endl;

        for (int i = 0; i < size; i++)
        {
            GLfloat value;
            file.read(reinterpret_cast<char *>(&value), sizeof(GLfloat));

            outVector.push_back(value);
        }
    }

    void Model::Load(const std::string &filePath) {
        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::in);
        ReadAssetInfo(file);

        short totalMeshes;
        file.read(reinterpret_cast<char *>(&totalMeshes), sizeof(short));
        std::cout << "totalMeshes " << totalMeshes << std::endl;

        for (int i = 0; i < totalMeshes; i++)
        {
            structs::Mesh mesh;

            // load vectors
            std::cout << "loading vertices" << std::endl;
            ReadGlFloatVector(file, mesh.vertices);
            std::cout << "loading colours" << std::endl;
            ReadGlFloatVector(file, mesh.colours);
            std::cout << "loading texCoords" << std::endl;
            ReadGlFloatVector(file, mesh.texCoords);

            // load texture
            GLenum textureType;
            file.read(reinterpret_cast<char *>(&textureType), sizeof(GLenum));
            std::cout << "textureType " << textureType << std::endl;

            size_t textureDataSize;
            file.read(reinterpret_cast<char *>(&textureDataSize), sizeof(size_t));
            std::cout << "textureDataSize  " << textureDataSize << std::endl;

            char *textureData = new char[textureDataSize];
            file.read(textureData, textureDataSize);

            mesh.texture = structs::Texture{textureType, textureDataSize, textureData};
            meshes.push_back(mesh);
        }

        std::cout << "mesh count " << meshes.size() << std::endl;
        file.close();
    }

    void Model::Save(const std::string &filePath) {
        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
        WriteAssetInfo(file, assetInfo);

        short totalMeshes = meshes.size();
        file.write(reinterpret_cast<char *>(&totalMeshes), sizeof(short));
        for (int i = 0; i < totalMeshes; i++)
        {
            structs::Mesh mesh = meshes.at(i);

            // write vectors
            WriteGlFloatVector(file, mesh.vertices);
            WriteGlFloatVector(file, mesh.colours);
            WriteGlFloatVector(file, mesh.texCoords);

            // write texture
            structs::Texture texture = mesh.texture;
            GLenum textureType = texture.textureType;
            size_t textureDataSize = texture.textureDataSize;
            file.write(reinterpret_cast<char *>(&textureType), sizeof(GLenum));
            file.write(reinterpret_cast<char *>(&textureDataSize), sizeof(size_t));

            std::cout << "saving " << textureType << ", " << textureDataSize << std::endl;

            char *textureData = texture.textureData;
            file.write(textureData, textureDataSize);
        }

        file.close();
    }
}