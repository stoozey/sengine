#include "managers/asset_manager.hpp"
#include "assets/asset.hpp"
#include "assets/font.hpp"
#include "assets/material.hpp"
#include "assets/model.hpp"
#include "assets/shader.hpp"
#include "assets/sound.hpp"
#include "assets/texture.hpp"

managers::AssetManager *g_AssetManager = new managers::AssetManager();

namespace managers {
    AssetManager::AssetManager(): assetMap() { }

    bool CompareStrings(const std::string &a, const std::string &b) {
        return (a < b);
    }

    void AssetManager::GetAssetNames(const structs::AssetType &assetType, std::vector<std::string> *outNames) {
        std::map<std::string, std::shared_ptr<assets::Asset>>::iterator iterator;
        for (iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator) {
            std::shared_ptr<assets::Asset> asset = iterator->second;
            structs::AssetInfo assetInfo = asset->GetAssetInfo();
            if (assetType != assetInfo.assetType) continue;

            std::string name = iterator->first;
            outNames->push_back(name);
        }

        std::sort(outNames->begin(), outNames->end(), CompareStrings);
    }

    std::shared_ptr<assets::Asset> AssetManager::GetAssetRaw(const std::string &assetPath) {
        auto find = assetMap.find(assetPath);
        return ((find == assetMap.end()) ? nullptr : find->second);
    }

    std::string AssetManager::GetAssetPathRaw(const std::string &folderName, const std::string &assetName) {
        return (ASSET_FILE_PREFIX + folderName + "/" + assetName + ASSET_FILE_SUFFIX);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Font>(const std::string &assetName) {
        return GetAssetPathRaw("font", assetName);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Material>(const std::string &assetName) {
        return GetAssetPathRaw("material", assetName);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Model>(const std::string &assetName) {
        return GetAssetPathRaw("model", assetName);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Shader>(const std::string &assetName) {
        return GetAssetPathRaw("shader", assetName);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Sound>(const std::string &assetName) {
        return GetAssetPathRaw("sound", assetName);
    }

    template<>
    std::string AssetManager::GetAssetPath<assets::Texture>(const std::string &assetName) {
        return GetAssetPathRaw("texture", assetName);
    }
}