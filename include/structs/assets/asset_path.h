#ifndef SENGINE_ASSET_PATH_H
#define SENGINE_ASSET_PATH_H

#include <string>

#include "structs/assets/asset_type.h"

namespace structs {
    struct AssetPath {
        const AssetType assetType;
        const std::string &path;

        [[nodiscard]] std::string GetPathPrefix() const {
            std::string pathPrefix = "assets/";
            switch (assetType)
            {
                case AssetType::Sprite:
                    pathPrefix += "sprite/";
                    break;

                case AssetType::Shader:
                    pathPrefix += "shader/";
                    break;

                case AssetType::Model:
                    pathPrefix += "model/";
                    break;
            }

            return pathPrefix;
        }

        std::string GetFullPath() {
            std::string prefix = GetPathPrefix();
            return (prefix + path + ".asset");
        }
    };
}

#endif //SENGINE_ASSET_PATH_H
