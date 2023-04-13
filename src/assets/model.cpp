#include <fstream>
#include <iostream>

#include "assets/model.h"

AssetInfo Model::assetInfo = AssetInfo{ AssetType::Model };

void WriteGlFloatVector(std::fstream &file, std::vector<GLfloat> &inVector) {
    uint32_t size = inVector.size();
    file.write(reinterpret_cast<char*>(&size), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(inVector.data()), static_cast<uint32_t>(size));
}

void ReadGlFloatVector(std::fstream &file, std::vector<GLfloat> &outVector) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));
    std::cout << "found size is " << size << std::endl;

    for (int i = 0; i < size; i++) {
        GLfloat value;
        file.read(reinterpret_cast<char*>(&value), sizeof(GLfloat));

        outVector.push_back(value);
    }
}

void Model::Load(const std::string &filePath) {
    std::fstream file;
    file.open(filePath, std::ios::binary | std::ios::in);
    ReadAssetInfo(file);

    short totalMeshes;
    file.read(reinterpret_cast<char*>(&totalMeshes), sizeof(short));
    std::cout << "totalMeshes " << totalMeshes << std::endl;

    for (int i = 0; i < totalMeshes; i++) {
        Mesh mesh;

        // load vectors
        std::cout << "loading vertices" << std::endl;
        ReadGlFloatVector(file, mesh.vertices);
        std::cout << "loading colours" << std::endl;
        ReadGlFloatVector(file, mesh.colours);
        std::cout << "loading texCoords" << std::endl;
        ReadGlFloatVector(file, mesh.texCoords);

        // load texture
        GLenum textureType;
        file.read(reinterpret_cast<char*>(&textureType), sizeof(GLenum));
        std::cout << "textureType " << textureType << std::endl;

        size_t textureDataSize;
        file.read(reinterpret_cast<char*>(&textureDataSize), sizeof(size_t));
        std::cout << "textureDataSize  " << textureDataSize << std::endl;

        char *textureData = new char[textureDataSize];
        file.read(textureData, textureDataSize);

        mesh.texture = Texture{ textureType, textureDataSize, textureData };
        meshes.push_back(mesh);
    }

    file.close();
}

void Model::Save(const std::string &filePath) {
    std::fstream file;
    file.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
    WriteAssetInfo(file, assetInfo);

    size_t totalMeshes = meshes.size();
    file.write(reinterpret_cast<char*>(&totalMeshes), sizeof(size_t));
    for (int i = 0; i < totalMeshes; i++) {
        Mesh mesh = meshes[i];

        // write vectors
        WriteGlFloatVector(file, mesh.vertices);
        WriteGlFloatVector(file, mesh.colours);
        WriteGlFloatVector(file, mesh.texCoords);

        // write texture
        Texture texture = mesh.texture;
        GLenum textureType = texture.textureType;
        file.write(reinterpret_cast<char*>(&textureType), sizeof(GLenum));

        size_t textureDataSize;
        file.write(reinterpret_cast<char*>(&textureDataSize), sizeof(size_t));

        std::cout << "saving " << textureType << ", " << textureDataSize << std::endl;

        char *textureData = texture.textureData;
        file.write(textureData, static_cast<signed long long>(textureDataSize));
    }

    file.close();
}