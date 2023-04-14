#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>

#include "assets/asset.h"
#include "structs/assets/asset_path.h"

namespace managers {
    class AssetManager {
    public:
        static assets::Asset *LoadAsset(structs::AssetPath &assetPath);
        static void UnLoadAsset(structs::AssetPath &assetPath);

        static assets::Asset *GetAsset(structs::AssetPath &assetPath);
        static bool AssetExists(structs::AssetPath &assetPath);
    private:
        static std::map<std::string, assets::Asset *> assets;
        static std::map<structs::AssetType, assets::Asset *> defaultAssets;
    };
}

extern managers::AssetManager *g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
