#include <stb.h>
#include <filesystem>
#include <iostream>

#include "assets/texture.hpp"
#include "structs/asset_info.hpp"
#include "enums/asset_type.hpp"
#include "core/log.hpp"

namespace assets {
    Texture::Texture() : Asset(enums::AssetType::Texture) {
        width = 0;
        height = 0;
        dataSize = 0;
        data = nullptr;

        textureId = 0;
    }

    Texture::~Texture() {
        Free();
    }

    void Texture::Save(const std::string &filePath) {
        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::out | std::ios::trunc);
        WriteAssetInfo(file);

        file.write(reinterpret_cast<char *>(&width), sizeof(int));
        file.write(reinterpret_cast<char *>(&height), sizeof(int));

        file.write(reinterpret_cast<char *>(&dataSize), sizeof(long long));
        file.write(reinterpret_cast<char *>(data), dataSize);

        file.close();
    }

    void Texture::Load(const std::string &filePath) {
        Free();

        std::fstream file;
        file.open(filePath, std::ios::binary | std::ios::in);
        ReadAssetInfo(file);

        file.read(reinterpret_cast<char *>(&width), sizeof(int));
        file.read(reinterpret_cast<char *>(&height), sizeof(int));

        file.read(reinterpret_cast<char *>(&dataSize), sizeof(long long));

        data = new unsigned char[dataSize];
        file.read(reinterpret_cast<char *>(data), dataSize);

        file.close();

        BindTexture();
    }

    void Texture::LoadFromFile(const std::string &filePath) {
        if (!std::filesystem::exists(filePath)) throw std::invalid_argument(filePath);

        stbi_set_flip_vertically_on_load(true);

        int totalChannels;
        data = stbi_load(filePath.c_str(), &width, &height, &totalChannels, 0);
        dataSize = (width * height * totalChannels);
    }

    void Texture::BindTexture() {
        //core::Log::Info("1");
        glGenTextures(1, &textureId);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::Free() {
        if (data) {
            stbi_image_free(data);
            glDeleteTextures(1, &textureId);
        }

        width = 0;
        height = 0;
        dataSize = 0;
        data = nullptr;
    }
}