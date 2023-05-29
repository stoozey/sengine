#include <fmt/format.h>

#include "core/log.hpp"
#include "exceptions/exception.hpp"
#include "exceptions/invalid_arguments.hpp"
#include "managers/asset_manager.hpp"

namespace managers {
    AssetManager::AssetManager() : assets() {
        LoadDefaultAssets();
    }

    AssetManager::~AssetManager() {
        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            xg::Guid guid = iterator->first;
            DeRegisterAsset(guid);
        }
    }

    void AssetManager::LoadDefaultAssets() {
        //LoadDefaultAsset<assets::Font>();
        //LoadDefaultAsset<assets::Material>();
        //LoadDefaultAsset<assets::Model>();
        core::Log::Info("LOADING SHADER");
        LoadDefaultAsset<assets::Shader>();
        //LoadDefaultAsset<assets::Sound>();
        core::Log::Info("LOADING TEXTURE");
        LoadDefaultAsset<assets::Texture>();
    }

    std::string AssetManager::GetAssetPath(const std::string &folderName, const std::string &name) {
        static std::string assetFilePrefix = "resources/assets/";
        static std::string assetFileSuffix = ".asset";

        return (assetFilePrefix + folderName + "/" + name + assetFileSuffix);
    }

    bool AssetManager::AssetExists(const std::string &path, bool mustBeLoaded) {
        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            AssetData assetData = iterator->second;
            if (assetData.path != path) continue;

            xg::Guid guid = assetData.guid;
            return AssetExists(guid, mustBeLoaded);
        }

        return false;
    }

    bool AssetManager::AssetExists(const xg::Guid &guid, bool mustBeLoaded) {
        try {
            const AssetData &assetData = GetAssetData(guid);
            if ((assetData.pointer == nullptr) && (mustBeLoaded)) return false;
        } catch (const exceptions::Exception &exception) {
            return false;
        }

        return true;
    }

    bool AssetManager::AssetIsLoaded(const xg::Guid &guid) {
        try {
            const AssetData &assetData = GetAssetData(guid);
            return (assetData.pointer != nullptr);
        } catch (const exceptions::Exception &exception) {
            return false;
        }
    }

    std::weak_ptr<assets::Asset> AssetManager::GetAsset(const xg::Guid &guid) {
        std::weak_ptr<assets::Asset> asset;
        try {
            const AssetData &assetData = GetAssetData(guid);
            asset = ((assetData.pointer == nullptr) ? std::weak_ptr<assets::Asset>() : std::weak_ptr<assets::Asset>(assetData.pointer));
        } catch (const exceptions::Exception &exception) {
            asset = std::weak_ptr<assets::Asset>();
        }

        return asset;
    }

    enums::AssetType AssetManager::AssetGetType(const xg::Guid &guid) {
        const AssetData &assetData = GetAssetData(guid);
        return assetData.assetType;
    }

    std::string AssetManager::AssetGetName(const xg::Guid &guid) {
        const AssetData &assetData = GetAssetData(guid);
        return assetData.name;
    }

    std::string AssetManager::AssetGetPath(const xg::Guid &guid) {
        const AssetData &assetData = GetAssetData(guid);
        return assetData.path;
    }

    std::vector<xg::Guid> AssetManager::GetAssetGuids(enums::AssetType assetType) {
        std::vector<xg::Guid> guids;
        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            AssetData assetData = iterator->second;
            if (assetData.assetType != assetType) continue;

            xg::Guid guid = assetData.guid;
            guids.emplace_back(guid);
        }

        return guids;
    }

    std::vector<xg::Guid> AssetManager::GetAllAssetGuids() {
        std::vector<xg::Guid> guids;
        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            AssetData assetData = iterator->second;
            xg::Guid guid = assetData.guid;
            guids.emplace_back(guid);
        }

        return guids;
    }

    void AssetManager::UnLoadAsset(const xg::Guid &guid) {
        if ((!AssetIsLoaded(guid)) || (!AssetExists(guid, false))) return;

        const AssetData &assetData = GetAssetData(guid);
        assetData.pointer.reset();
        assetData.pointer.reset();
    }

    void AssetManager::RegisterAsset(const AssetData &assetData) {
        xg::Guid guid = assetData.guid;
        assets[guid] = assetData;
    }

    void AssetManager::DeRegisterAsset(const xg::Guid &guid) {
        try {
            UnLoadAsset(guid);
        } catch (const exceptions::Exception &exception) {
            return;
        }

        assets.erase(guid);
    }

    const AssetManager::AssetData &AssetManager::GetAssetData(const std::string &path) {
        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            const AssetData &assetData = iterator->second;
            if (assetData.path == path) return assetData;
        }

        throw exceptions::InvalidArguments(fmt::format("GetAssetData of path \"{}\" doesn't exist", path));
    }

    const AssetManager::AssetData &AssetManager::GetAssetData(const xg::Guid &guid) {
        auto find = assets.find(guid);
        if (find == assets.end()) throw exceptions::InvalidArguments(fmt::format("GetAssetData of path \"{}\" doesn't exist", guid.str()));

        return find->second;
    }
}