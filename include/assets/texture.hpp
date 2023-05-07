#ifndef SENGINE_TEST1_TEXTURE1_H
#define SENGINE_TEST1_TEXTURE1_H

#include "assets/asset.hpp"
#include "structs/assets/asset_info.hpp"

namespace assets {
    class Texture : public Asset {
    public:
        Texture();
        ~Texture();

        void Save(const std::string &filePath);
        void Load(const std::string &filePath);
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
