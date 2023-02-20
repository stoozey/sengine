#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>

#include "assets/asset.h"
#include "datatypes/asset_path.h"

class AssetManager {
public:
    static Asset *LoadAsset(AssetPath& assetPath);
    static void UnLoadAsset(AssetPath& assetPath);

    static Asset *GetAsset(AssetPath& assetPath);
    static bool AssetExists(AssetPath& assetPath);
private:
    static std::map<std::string, Asset*> assets;
};

//extern AssetManager *g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
