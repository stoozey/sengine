#ifndef SENGINE_TEST1_TEXTURE1_H
#define SENGINE_TEST1_TEXTURE1_H

#include "assets/asset.h"

namespace assets {
    class Texture : public Asset {
    public:
        Texture();
        ~Texture();

        void Save(const std::string &filePath);
        void Load(const std::string &filePath);
        void LoadFromFile(const std::string &filePath);
    private:
        static structs::AssetInfo assetInfo;

        int width;
        int height;
        size_t dataSize;
        unsigned char *data;
    };
}

#endif //SENGINE_TEST1_TEXTURE1_H
