#include <stb.h>
#include <filesystem>
#include <iostream>

#include "assets/texture.h"
#include "structs/assets/asset_info.h"
#include "structs/assets/asset_type.h"

namespace assets {
    structs::AssetInfo Texture::assetInfo{ structs::AssetType::Texture };

    Texture::Texture() {
        width = 0;
        height = 0;
        dataSize = 0;
        data = nullptr;
    }

    Texture::~Texture() {
        Free();
    }

    void Texture::Save(const std::string &filePath) {
        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
        WriteAssetInfo(file, assetInfo);

        file.write(reinterpret_cast<char*>(&width), sizeof(int));
        file.write(reinterpret_cast<char*>(&height), sizeof(int));

        file.write(reinterpret_cast<char*>(&dataSize), sizeof(long long));
        file.write(reinterpret_cast<char*>(data), dataSize);

        file.close();
        std::cout << "saving as w: " << width << ", h: " << height << ", size: " << dataSize << std::endl;

    }

    void Texture::Load(const std::string &filePath) {
        Free();

        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::in);
        ReadAssetInfo(file);

        file.read(reinterpret_cast<char*>(&width), sizeof(int));
        file.read(reinterpret_cast<char*>(&height), sizeof(int));

        file.read(reinterpret_cast<char*>(&dataSize), sizeof(long long));

        data = new unsigned char[dataSize];
        file.read(reinterpret_cast<char*>(data), dataSize);

        file.close();
    }

    void Texture::LoadFromFile(const std::string &filePath) {
        if (!std::filesystem::exists(filePath)) throw std::invalid_argument(filePath);

        stbi_set_flip_vertically_on_load(true);

        int totalChannels;
        data = stbi_load(filePath.c_str(), &width, &height, &totalChannels, 0);
        dataSize = (width * height * totalChannels);
        std::cout << dataSize << std::endl;
    }

    void Texture::Free() {
        if (data) {
            stbi_image_free(data);
        }

        width = 0;
        height = 0;
        dataSize = 0;
        data = nullptr;
    }
}