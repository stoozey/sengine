#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>
#include <filesystem>
#include <utility>

#include "core/log.hpp"
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
        std::shared_ptr<T> LoadAsset(const std::string &assetName);

        template<typename T>
        void UnLoadAsset(const std::string &assetName);

        template<typename T>
        std::shared_ptr<T> GetAsset(const std::string &assetName);

        template<typename T>
        bool AssetExists(const std::string &assetName);

        template<typename T>
        std::shared_ptr<T> GetDefaultAsset();

        template<typename T>
        std::string GetAssetPath(const std::string &assetName);
    private:
        std::map<std::string, std::shared_ptr<assets::Asset>> assets;
    };
}

extern managers::AssetManager *g_AssetManager;

#include "asset_manager.tpp"
#endif //SENGINE_ASSET_MANAGER_H
