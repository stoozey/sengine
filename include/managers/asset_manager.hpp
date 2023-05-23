#ifndef SENGINE_ASSET_MANAGER_H
#define SENGINE_ASSET_MANAGER_H

#include <memory>
#include <filesystem>
#include <utility>
#include <map>
#include <typeindex>
#include <typeinfo>

#include "managers/manager.hpp"
#include "core/log.hpp"
#include "structs/assets/asset_type.hpp"
#include "assets/asset.hpp"
#include "assets/font.hpp"
#include "assets/material.hpp"
#include "assets/model.hpp"
#include "assets/shader.hpp"
#include "assets/sound.hpp"
#include "assets/texture.hpp"

namespace managers {
    const std::string ASSET_DEFAULT_NAME = ".default";
    const std::string ASSET_FILE_PREFIX = "resources/assets/";
    const std::string ASSET_FILE_SUFFIX = ".asset";

    const std::string DEFAULT_ASSET_NAME = ".default";

    const std::unordered_map<std::type_index, std::string> ASSET_FOLDER_NAMES = {
            { typeid(assets::Font), "font" },
            { typeid(assets::Material), "material" },
            { typeid(assets::Model), "model" },
            { typeid(assets::Shader), "shader" },
            { typeid(assets::Sound), "sound" },
            { typeid(assets::Texture), "texture" }
    };

    const std::unordered_map<std::type_index, structs::AssetType> ASSET_ASSET_TYPES = {
            { typeid(assets::Font), structs::AssetType::Font },
            { typeid(assets::Material), structs::AssetType::Material },
            { typeid(assets::Model), structs::AssetType::Model },
            { typeid(assets::Shader), structs::AssetType::Shader },
            { typeid(assets::Sound), structs::AssetType::Sound },
            { typeid(assets::Texture), structs::AssetType::Texture }
    };

    class AssetManager : public Manager {
    public:
        AssetManager();
        ~AssetManager();

        void GetAssetNames(const structs::AssetType &assetType, std::vector<std::string> *outNames);
        std::shared_ptr<assets::Asset> GetAssetRaw(const std::string &assetPath);
        static std::string GetAssetPathRaw(const std::string &folderName, const std::string &assetName);


        template<typename T>
        structs::AssetType GetAssetType();

        template<typename T>
        std::shared_ptr<T> LoadAsset(const std::string &assetName, bool loadDefaultIfFailed = true);

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
        std::map<std::string, std::shared_ptr<assets::Asset>> assetMap;
    };
}

#include "managers/asset_manager.tpp"
#endif //SENGINE_ASSET_MANAGER_H
