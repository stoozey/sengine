#include <stb.h>
#include <filesystem>

#include "assets/texture.h"

namespace assets {
    void Texture::Save(const std::string &filePath) {

    }

    void Texture::Load(const std::string &filePath) {

    }

    //Texture Texture::FromFile(const std::string &filePath) {
    //    //if (!std::filesystem::exists(filePath)) throw std::invalid_argument(std::format("file"));
    //
    //    stbi_set_flip_vertically_on_load(true);
    //
    //    int imageWidth, imageHeight, channelsCount;
    //    unsigned char *bytes = stbi_load(filePath.c_str(), &imageWidth, &imageHeight, &channelsCount, 0);
    //}
}