#ifndef SENGINE_TEST1_TEXTURE1_H
#define SENGINE_TEST1_TEXTURE1_H

#include "assets/asset.h"

namespace assets {
    class Texture : public Asset {
    public:
        static Texture FromFile(const std::string &filePath);

        void Save(const std::string &filePath);
        void Load(const std::string &filePath);
    private:
        static structs::AssetInfo assetInfo;

        unsigned int width;
        unsigned int height;
        size_t dataSize;
        char *data;
    };
}

#endif //SENGINE_TEST1_TEXTURE1_H
