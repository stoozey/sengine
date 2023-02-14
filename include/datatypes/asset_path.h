#ifndef SENGINE_ASSET_PATH_H
#define SENGINE_ASSET_PATH_H

#include <string>

const char *ASSET_EXTENSION = "asset";

enum class AssetType {
    Sprite
};

template<AssetType T>
struct AssetPath {
    const std::string& path;

    std::string GetPathPrefix() {
        std::string pathPrefix = "datafiles/";
        switch (T) {
            case AssetType::Sprite:
                pathPrefix += "sprite/";
        }

        return pathPrefix;
    }

    const std::string GetFullPath() {
        std::string prefix = GetPathPrefix();
        return (prefix + path + "." + ASSET_EXTENSION);
    }
};

#endif //SENGINE_ASSET_PATH_H
