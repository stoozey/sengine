#include <filesystem>

#include "managers/asset_manager.h"
#include "assets/sprite.h"


//AssetManager *g_AssetManager = new AssetManager();

std::map<std::string, Asset*> AssetManager::assets = std::map<std::string, Asset*>();

Asset *AssetManager::LoadAsset(AssetPath& assetPath) {
    const std::string path = assetPath.GetFullPath();
    Asset *asset = GetAsset(assetPath);
    if ((std::filesystem::exists(path)) && (asset == nullptr)) {
        switch (assetPath.assetType) {
            case AssetType::Sprite: {
                asset = new Sprite(nullptr);
                break;
            }
        }

        asset->Load(path);
        assets.insert({path, asset});
    }

    return asset;
}

void AssetManager::UnLoadAsset(AssetPath& assetPath) {
    const std::string path = assetPath.GetFullPath();
    auto find = assets.find(path);
    if (find == assets.end()) return;

    assets.erase(find);
    delete find->second;
}

Asset *AssetManager::GetAsset(AssetPath& assetPath) {
    const std::string path = assetPath.GetFullPath();
    auto find = assets.find(path);
    return ((find == assets.end()) ? nullptr : find->second);
}

bool AssetManager::AssetExists(AssetPath& assetPath) {
    return (GetAsset(assetPath) != nullptr);
}