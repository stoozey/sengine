#include <stb.h>
#include <filesystem>

#include "assets/texture.h"

namespace assets {
    Texture::Texture() {
        width = 0;
        height = 0;
        dataSize = 0;
        data = nullptr;
    }

    Texture::~Texture() {
        if (data) {
            stbi_image_free(data);
        }
    }

    void Texture::Save(const std::string &filePath) {

    }

    void Texture::Load(const std::string &filePath) {

    }

    void Texture::LoadFromFile(const std::string &filePath) {
        if (!std::filesystem::exists(filePath)) throw std::invalid_argument(filePath);

        stbi_set_flip_vertically_on_load(true);

        int totalChannels;
        data = stbi_load(filePath.c_str(), &width, &height, &totalChannels, 0);
        dataSize = (width * totalChannels);
    }
}