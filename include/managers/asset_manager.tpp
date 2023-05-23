#ifndef SENGINE_ASSET_MANAGER_TPP
#define SENGINE_ASSET_MANAGER_TPP

#include "managers/asset_manager.hpp"

namespace managers {
    template<typename T>
    structs::AssetType AssetManager::GetAssetType() {
        auto find = ASSET_ASSET_TYPES.find(typeid(T));
        if (find == ASSET_ASSET_TYPES.end()) core::Log::Error("asset type for typeid \"{}\" doesn't exist", typeid(T).name());

        return find->second;
    }

    template<typename T>
    std::shared_ptr<T> AssetManager::LoadAsset(const std::string &assetName, bool loadDefaultIfFailed) {
        std::shared_ptr<T> asset;
        std::string assetPath = GetAssetPath<T>(assetName);
        core::Log::Info("loading asset {}", assetPath);

        try {
            asset = GetAsset<T>(assetPath);
            if ((std::filesystem::exists(assetPath)) && (asset == nullptr)) {
                asset = std::make_shared<T>();
                asset->Load(assetPath);
                assetMap.insert({ assetPath, asset });
            }
        }
        catch(const std::exception &e) {
            core::Log::Warn("an error occured when trying to get asset ", assetName, ":", e.what());
            asset = nullptr;
        }

        if (asset == nullptr) {
            core::Log::Warn("asset \"{}\" not found, using default", assetPath);

            const std::string defaultAssetPath = GetAssetPath<T>(ASSET_DEFAULT_NAME);
            if (!std::filesystem::exists(defaultAssetPath)) core::Log::Error("missing default asset \"{}\"", defaultAssetPath);

            asset = LoadAsset<T>(ASSET_DEFAULT_NAME, false);
        }

        return asset;
    }

    template<typename T>
    void AssetManager::UnLoadAsset(const std::string &assetName) {
        const std::string assetPath = GetAssetPath<T>(assetName);
        auto find = assetMap.find(assetPath);
        if (find == assetMap.end()) return;

        assetMap.erase(find);
    }

    template<typename T>
    std::shared_ptr<T> AssetManager::GetAsset(const std::string &assetName) {
        const std::string assetPath = GetAssetPath<T>(assetName);
        std::shared_ptr<assets::Asset> asset = GetAssetRaw(assetPath);
        return dynamic_pointer_cast<T>((asset == nullptr) ? nullptr : asset);
    }

    template<typename T>
    bool AssetManager::AssetExists(const std::string &assetName) {
        return (GetAsset<T>(assetName) != nullptr);
    }

    template<typename T>
    std::shared_ptr<T> AssetManager::GetDefaultAsset() {
        return LoadAsset<T>(DEFAULT_ASSET_NAME, false);
    }

    template<typename T>
    std::string AssetManager::GetAssetPath(const std::string &assetName) {
        auto find = ASSET_FOLDER_NAMES.find(typeid(T));
        if (find == ASSET_FOLDER_NAMES.end()) core::Log::Error("asset folder name for \"{}\" doesn't exist", assetName);

        std::string folderName = find->second;
        return GetAssetPathRaw(folderName, assetName);
    }
}

#endif //SENGINE_ASSET_MANAGER_TPP