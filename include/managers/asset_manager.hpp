#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>
#include <filesystem>
#include <spdlog/spdlog.h>

#include "assets/asset.hpp"
#include "assets/shader.hpp"
#include "assets/model.hpp"
#include "assets/texture.hpp"

namespace managers {
    const std::string ASSET_DEFAULT_NAME = ".default";
    const std::string ASSET_FILE_PREFIX = "resources/assets/";
    const std::string ASSET_FILE_SUFFIX = ".asset";

    class AssetManager {
    public:
        AssetManager();

        template<typename T>
        T *LoadAsset(const std::string &assetName) {
            const std::string assetPath = GetAssetPath<T>(assetName);
            T *asset = GetAsset<T>(assetName);
            if ((std::filesystem::exists(assetPath)) && (asset == nullptr)) {
                asset = new T();
                asset->Load(assetPath);
                assets.insert({ assetPath, asset });
            }

            if (asset == nullptr) {
                const std::string defaultAssetPath = GetAssetPath<T>(ASSET_DEFAULT_NAME);
                spdlog::warn("asset \"" + assetPath + "\" not found, using default");
                if (!std::filesystem::exists(defaultAssetPath)) {
                    spdlog::critical("missing default asset \"" + defaultAssetPath + "\"");
                    throw;
                }

                asset = LoadAsset<T>(ASSET_DEFAULT_NAME);
            }

            return asset;
        }

        template<typename T>
        void UnLoadAsset(const std::string &assetName) {
            const std::string assetPath = GetAssetPath<T>(assetName);
            auto find = assets.find(assetPath);
            if (find == assets.end()) return;

            assets.erase(find);
            delete find->second;
        }

        template<typename T>
        T *GetAsset(const std::string &assetName) {
            const std::string assetPath = GetAssetPath<T>(assetName);
            auto find = assets.find(assetPath);
            return dynamic_cast<T *>(((find == assets.end()) ? nullptr : find->second));
        }

        template<typename T>
        bool AssetExists(const std::string &assetName) {
            return (GetAsset<T>(assetName) != nullptr);
        }

        template<typename T>
        T *GetDefaultAsset() {
            return LoadAsset<T>(".default");
        };

        template<typename T>
        std::string GetAssetPath(const std::string &assetName);
    private:
        std::map<std::string, assets::Asset *> assets;
        std::map<structs::AssetType, assets::Asset *> defaultAssets;
    };
}

extern managers::AssetManager *g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
