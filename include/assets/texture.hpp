#ifndef SENGINE_TEST1_TEXTURE1_H
#define SENGINE_TEST1_TEXTURE1_H

#include <glad.h>

#include "assets/asset.hpp"
#include "structs/asset_info.hpp"

namespace assets {
    class Texture : public Asset {
    public:
        Texture();
        ~Texture();

        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;
        void LoadFromFile(const std::string &filePath);

        int width;
        int height;
        long long dataSize;
        unsigned char *data;

        GLuint textureId;
    private:
        void BindTexture();
        void Free();
    };
}

#endif //SENGINE_TEST1_TEXTURE1_H
