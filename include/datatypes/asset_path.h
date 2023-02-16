#ifndef SENGINE_ASSET_PATH_H
#define SENGINE_ASSET_PATH_H

#include <string>

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

    std::string GetFullPath() {
        std::string prefix = GetPathPrefix();
        return (prefix + path + ".asset");
    }
};

#endif //SENGINE_ASSET_PATH_H
