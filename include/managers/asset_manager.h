#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include "assets/asset.h"
#include "datatypes/asset_path.h"

class AssetManager {
public:
    template<AssetType T> Asset *LoadAsset(AssetPath<T> assetPath);
    template<AssetType T> void UnLoadAsset(AssetPath<T> assetPath);
    template<AssetType T> Asset *GetAsset(AssetPath<T> assetPath);
    template<AssetType T> bool AssetExists(AssetPath<T> assetPath);
private:
    template<AssetType T> void AddToAssets(AssetPath<T> assetPath, Asset *asset);

    std::map<std::string, Asset*> assets;
};

extern AssetManager g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
