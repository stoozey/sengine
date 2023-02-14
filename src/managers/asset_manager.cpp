#include <filesystem>

#include "managers/asset_manager.h"
#include "assets/sprite.h"

namespace fs = std::filesystem;

AssetManager *g_AssetManager = new AssetManager();

template<AssetType T>
Asset *AssetManager::LoadAsset(const AssetPath<T>& assetPath) {
    const std::string path = assetPath.GetFullPath();
    Asset *asset = GetAsset(assetPath);
    if ((fs::exists(path)) && (asset == nullptr)) {
        switch (T) {
            case AssetType::Sprite: {
                asset = new Sprite(path, nullptr);
                break;
            }
        }

        assets.insert({path, asset});
    }

    return asset;
}

template<AssetType T>
void AssetManager::UnLoadAsset(const AssetPath<T>& assetPath) {
    const std::string path = assetPath.GetFullPath();
    auto find = assets.find(path);
    if (find == assets.end()) return;

    assets.erase(find);
    delete find->second;
}

template<AssetType T>
Asset *AssetManager::GetAsset(const AssetPath<T>& assetPath) {
    const std::string path = assetPath.GetFullPath();
    auto find = assets.find(path);
    return ((find == assets.end()) ? nullptr : find->second);
}

template<AssetType T>
bool AssetManager::AssetExists(const AssetPath<T>& assetPath) {
    return (GetAsset(assetPath) != nullptr);
}