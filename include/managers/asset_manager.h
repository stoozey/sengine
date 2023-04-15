#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>

#include "assets/asset.h"
#include "assets/sprite.h"
#include "assets/shader.h"
#include "assets/model.h"
#include "assets/texture.h"

namespace managers {
    const std::string ASSET_DEFAULT_NAME = ".default";
    const std::string ASSET_FILE_PREFIX = "assets/";
    const std::string ASSET_FILE_SUFFIX = ".asset";

    class AssetManager {
    public:
        AssetManager();

        template<typename T>
        T *LoadAsset(const std::string &assetName) {
            const std::string assetPath = GetAssetPath<T>(assetName);
            T *asset = GetAsset<T>(assetName);
            if ((std::filesystem::exists(assetPath)) && (asset == nullptr))
            {
                asset = new T();
                asset->Load(assetPath);
                assets.insert({assetPath, asset});
            } else {
                const std::string defaultAssetPath = GetAssetPath<T>(ASSET_DEFAULT_NAME);
                std::cout << "not found, using default: " << defaultAssetPath << std::endl;
                if (!std::filesystem::exists(defaultAssetPath)) throw std::invalid_argument(assetPath);

                return LoadAsset<T>(ASSET_DEFAULT_NAME);
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
            return dynamic_cast<T*>(((find == assets.end()) ? nullptr : find->second));
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
        std::map<std::string, assets::Asset*> assets;
        std::map<structs::AssetType, assets::Asset*> defaultAssets;
    };
}

extern managers::AssetManager *g_AssetManager;

#endif //SENGINE_ASSET_MANAGER_H
