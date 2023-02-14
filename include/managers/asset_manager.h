#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include "assets/asset.h"
#include "datatypes/asset_path.h"

class AssetManager {
public:
    template<AssetType T> Asset *LoadAsset(const AssetPath<T> &assetPath);
    template<AssetType T> void UnLoadAsset(const AssetPath<T> &assetPath);
    template<AssetType T> Asset *GetAsset(const AssetPath<T> &assetPath);
    template<AssetType T> bool AssetExists(const AssetPath<T> &assetPath);
private:
    template<AssetType T> void AddToAssets(const AssetPath<T> &assetPath, Asset *asset);

    std::map<std::string, Asset*> assets;
};

extern AssetManager g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
