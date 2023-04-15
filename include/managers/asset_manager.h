#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>

#include "assets/asset.h"
#include "structs/assets/asset_path.h"

namespace managers {
    class AssetManager {
    public:
        AssetManager();

        assets::Asset *LoadAsset(const structs::AssetPath &assetPath);
        void UnLoadAsset(const structs::AssetPath &assetPath);

        assets::Asset *GetAsset(const structs::AssetPath &assetPath);
        bool AssetExists(const structs::AssetPath &assetPath);

        assets::Asset *GetDefaultAsset(structs::AssetType assetType);
    private:
        std::map<std::string, assets::Asset*> assets;
        std::map<structs::AssetType, assets::Asset*> defaultAssets;
    };
}

extern managers::AssetManager *g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
