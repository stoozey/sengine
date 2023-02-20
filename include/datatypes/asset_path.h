#ifndef SENGINE_ASSET_PATH_H
#define SENGINE_ASSET_PATH_H

#include <string>

enum class AssetType {
    Sprite
};

struct AssetPath {
    const AssetType assetType;
    const std::string& path;

    std::string GetPathPrefix() {
        std::string pathPrefix = "resources/";
        switch (assetType) {
            case AssetType::Sprite:
                pathPrefix += "sprite/";
        }

        return pathPrefix;
    }

    std::string GetFullPath() {
        std::string prefix = GetPathPrefix();
        return (prefix + path + ".asset");
    }
};

#endif //SENGINE_ASSET_PATH_H
