#include <fstream>
#include <iostream>

#include "assets/model.h"

AssetInfo Model::assetInfo = AssetInfo{ AssetType::Model };

void WriteGlFloatVector(std::fstream &file, std::vector<GLfloat> &inVector) {
    uint32_t size = inVector.size();
    file.write(reinterpret_cast<char*>(size), sizeof(uint32_t));
    file.write(reinterpret_cast<char*>(inVector.data()), static_cast<uint32_t>(sizeof(GLfloat) * size));
}

void ReadGlFloatVector(std::fstream &file, std::vector<GLfloat> &outVector) {
    int size;
    file.read(reinterpret_cast<char*>(&size), sizeof(int));

    for (int i = 0; i < size; i++) {
        GLfloat value;
        file.read(reinterpret_cast<char*>(&value), sizeof(GLfloat));

        outVector.push_back(value);
    }
}

void Model::Load(const std::string &filePath) {
    std::fstream file;
    file.open(filePath, std::ios::in);
    ReadAssetInfo(file);

    short totalMeshes;
    file.read(reinterpret_cast<char*>(&totalMeshes), sizeof(short));

    for (int i = 0; i < totalMeshes; i++) {
        Mesh mesh;
        ReadGlFloatVector(file, mesh.vertices);
        ReadGlFloatVector(file, mesh.colours);
        ReadGlFloatVector(file, mesh.texCoords);

        // load texture
        GLenum textureType;
        file.read(reinterpret_cast<char*>(&textureType), sizeof(GLenum));

        size_t pos = file.tellg();
        file.seekg(0, std::fstream::end);
        size_t endPos = file.tellg();
        size_t sizeLeft = (endPos - pos);
        file.seekg(pos, std::fstream::beg);

        char *textureData;
        file.read(textureData, sizeLeft);
        mesh.texture = { textureType, textureData };
        meshes.push_back(mesh);
    }

    file.close();
}

void Model::Save(const std::string &filePath) {
    std::fstream file;
    file.open(filePath, std::ios::out);
    WriteAssetInfo(file, assetInfo);

    short totalMeshes = static_cast<short>(meshes.size());
    file.write(reinterpret_cast<char*>(totalMeshes), sizeof(short));

    for (int i = 0; i < totalMeshes; i++) {
        Mesh mesh = meshes[i];
        WriteGlFloatVector(file, mesh.vertices);
        WriteGlFloatVector(file, mesh.colours);
        WriteGlFloatVector(file, mesh.texCoords);

        // load texture
        Texture texture = mesh.texture;
        GLenum textureType = texture.textureType;
        file.write(reinterpret_cast<char*>(textureType), sizeof(GLenum));

        char *textureData = texture.textureData;
        file.write(textureData, sizeof(textureData));
    }

    file.close();
}