#ifndef SENGINE_ASSET_PATH_H
#define SENGINE_ASSET_PATH_H

#include <string>

enum class AssetType {
    Sprite
};

template<AssetType T>
struct AssetPath {
    std::string path;

    const char *GetPathPrefix() {
        switch (T) {
            case AssetType::Sprite:
                return "sprite/";
        }
    }

    const char *GetFullPath() {
        const char *prefix = GetPathPrefix();

    }
};

#endif //SENGINE_ASSET_PATH_H
