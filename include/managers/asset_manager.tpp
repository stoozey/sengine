#ifndef SENGINE_ASSET_CREATOR_ASSET_MANAGER_TPP
#define SENGINE_ASSET_CREATOR_ASSET_MANAGER_TPP

#include <fmt/format.h>
#include <type_traits>
#include <filesystem>

#include "core/log.hpp"
#include "utils/asset_util.hpp"
#include "exceptions/invalid_template.hpp"

namespace managers {
    template<typename T>
    std::string AssetManager::GetAssetPath(const std::string &name) {
        AssertTemplateIsAsset<T>();

        static std::unordered_map<std::type_index, std::string> assetFolderNames = {
                { typeid(assets::Font), "font" },
                { typeid(assets::Material), "material" },
                { typeid(assets::Model), "model" },
                { typeid(assets::Shader), "shader" },
                { typeid(assets::Sound), "sound" },
                { typeid(assets::Texture), "texture" }
        };

        auto find = assetFolderNames.find(typeid(T));
        if (find == assetFolderNames.end()) throw exceptions::InvalidTemplate(fmt::format("type \"{}\" doesn't exist in AssetManager::AssetFolderNames", typeid(T).name()));

        std::string folderName = find->second;
        return GetAssetPath(folderName, name);
    }

    template<typename T>
    bool AssetManager::AssetExists(const std::string &name, bool mustBeLoaded) {
        AssertTemplateIsAsset<T>();

        std::string path = GetAssetPath<T>(name);
        return AssetExists(path, mustBeLoaded);
    }

    template<typename T>
    std::weak_ptr<T> AssetManager::GetAsset(const std::string &name) {
        AssertTemplateIsAsset<T>();

        enums::AssetType assetType = utils::GetAssetType<T>();

        std::unordered_map<xg::Guid, AssetData>::iterator iterator;
        for (iterator = assets.begin(); iterator != assets.end(); ++iterator) {
            AssetData assetData = iterator->second;
            if ((assetData.assetType != assetType) || (assetData.name != name)) continue;
            if (assetData.pointer == nullptr) break;

            return std::weak_ptr<T>(std::static_pointer_cast<T>(assetData.pointer));
        }

        return std::weak_ptr<T>();
    }

    template<typename T>
    std::shared_ptr<T> AssetManager::GetAssetOrDefault(const std::string &name) {
        auto assetPtr = GetAsset<T>(name);
        if (auto lock = assetPtr.lock()) return lock;

        static auto assetManager = g_Engine->GetManager<managers::AssetManager>();
        auto defaultAsset = assetManager->GetDefaultAsset<T>();
        return defaultAsset.lock();
    }

    template<typename T>
    std::shared_ptr<T> AssetManager::GetAssetOrDefault(std::weak_ptr<T> assetPtr) {
        if (auto lock = assetPtr.lock()) return lock;

        static auto assetManager = g_Engine->GetManager<managers::AssetManager>();
        auto defaultAsset = assetManager->GetDefaultAsset<T>();
        return defaultAsset.lock();
    }

    template<typename T>
    std::vector<xg::Guid> AssetManager::GetAssetGuids() {
        AssertTemplateIsAsset<T>();

        enums::AssetType assetType = utils::GetAssetType<T>();
        return GetAssetGuids(assetType);
    }

    template<typename T>
    std::weak_ptr<T> AssetManager::GetDefaultAsset() {
        AssertTemplateIsAsset<T>();

        return GetAsset<T>(DEFAULT_ASSET_NAME);
    }

    template<typename T>
    bool AssetManager::LoadAsset(const std::string &name) {
        AssertTemplateIsAsset<T>();

        std::string path = GetAssetPath<T>(name);
        if (AssetExists(path, true)) return true;

        if (!std::filesystem::exists(path)) {
            core::Log::Warn(fmt::format("tried to load asset from \"{}\", but the file doesn't exist", path));
            return false;
        }

        std::shared_ptr<T> asset = nullptr;
        try {
            core::Log::Info(fmt::format("loading asset from \"{}\"", path));

            asset = std::make_shared<T>();
            asset->Load(path);
        } catch (...) {
            asset = nullptr;
        }

        if (asset == nullptr) return false;

        if (AssetExists(path, false)) {
            const AssetData &assetData = GetAssetData(path);
            assetData.pointer = asset;
        } else {
            enums::AssetType assetType = utils::GetAssetType<T>();
            AssetData assetData = AssetData{ asset->GetGuid(), assetType, asset, name, path };
            RegisterAsset(assetData);
        }

        return true;
    }

    template<typename T>
    bool AssetManager::LoadDefaultAsset() {
        return LoadAsset<T>(DEFAULT_ASSET_NAME);
    }

    template<typename T>
    void AssetManager::ReLoadAsset(const xg::Guid &guid) {
        const AssetData &assetData = GetAssetData(guid);
        UnLoadAsset(guid);
        LoadAsset<T>(assetData.name);
    }

    template<typename T>
    void AssetManager::AssertTemplateIsAsset() {
        if (std::is_base_of<assets::Asset, T>::value) return;

        throw exceptions::InvalidTemplate(fmt::format("template \"{}\" is not derived from Asset", typeid(T).name()));
    }

    template<typename T>
    const AssetManager::AssetData &AssetManager::GetAssetData(const std::string &name) {
        AssertTemplateIsAsset<T>();

        std::string path = GetAssetPath<T>(name);
        return GetAssetData(path);
    }
}

#endif //SENGINE_ASSET_CREATOR_ASSET_MANAGER_TPP
