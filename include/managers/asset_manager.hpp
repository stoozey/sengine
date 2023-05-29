#ifndef SENGINE_ASSET_CREATOR_ASSET_MANAGER_HPP
#define SENGINE_ASSET_CREATOR_ASSET_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include <crossguid/guid.hpp>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <vector>

#include "enums/asset_type.hpp"
#include "managers/manager.hpp"
#include "assets/asset.hpp"
#include "assets/font.hpp"
#include "assets/material.hpp"
#include "assets/model.hpp"
#include "assets/shader.hpp"
#include "assets/sound.hpp"
#include "assets/texture.hpp"

const std::string DEFAULT_ASSET_NAME = ".default";

namespace managers {
    class AssetManager : public Manager {
    public:
        struct AssetData {
            xg::Guid guid;
            enums::AssetType assetType;
            mutable std::shared_ptr<assets::Asset> pointer;
            std::string name;
            std::string path;
        };

        AssetManager();
        ~AssetManager();

        template<typename T>
        static std::string GetAssetPath(const std::string &name);
        static std::string GetAssetPath(const std::string &folderName, const std::string &name);

        template<typename T>
        bool AssetExists(const std::string &name, bool mustBeLoaded = true);
        bool AssetExists(const std::string &path, bool mustBeLoaded = true);
        bool AssetExists(const xg::Guid &guid, bool mustBeLoaded = true);

        bool AssetIsLoaded(const xg::Guid &guid);

        template<typename T>
        std::weak_ptr<T> GetAsset(const std::string &name);
        std::weak_ptr<assets::Asset> GetAsset(const xg::Guid &guid);

        enums::AssetType AssetGetType(const xg::Guid &guid);
        std::string AssetGetName(const xg::Guid &guid);
        std::string AssetGetPath(const xg::Guid &guid);

        template<typename T>
        std::vector<xg::Guid> GetAssetGuids();
        std::vector<xg::Guid> GetAssetGuids(enums::AssetType assetType);
        std::vector<xg::Guid> GetAllAssetGuids();

        template<typename T>
        std::weak_ptr<T> GetDefaultAsset();

        template<typename T>
        bool LoadAsset(const std::string &name);
        void UnLoadAsset(const xg::Guid &guid);

        template<typename T>
        void ReLoadAsset(const xg::Guid &guid);

        void LoadDefaultAssets();
    private:
        std::unordered_map<xg::Guid, AssetData> assets;

        template<typename T>
        static void AssertTemplateIsAsset();

        template<typename T>
        bool LoadDefaultAsset();

        template<typename T>
        const AssetData &GetAssetData(const std::string &name);
        const AssetData &GetAssetData(const std::string &path);
        const AssetData &GetAssetData(const xg::Guid &guid);

        void RegisterAsset(const AssetData &assetData);
        void DeRegisterAsset(const xg::Guid &guid);
    };
}

#include "managers/asset_manager.tpp"
#endif //SENGINE_ASSET_CREATOR_ASSET_MANAGER_HPP
