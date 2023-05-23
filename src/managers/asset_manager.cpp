#include "utils/string_util.hpp"
#include "managers/asset_manager.hpp"

namespace managers {
    AssetManager::AssetManager() : assetMap() {
        //GetDefaultAsset<assets::Font>();
        //GetDefaultAsset<assets::Material>();
        //GetDefaultAsset<assets::Model>();
        GetDefaultAsset<assets::Shader>();
        //GetDefaultAsset<assets::Sound>();
        GetDefaultAsset<assets::Texture>();
    }

    AssetManager::~AssetManager() = default;

    void AssetManager::GetAssetNames(const structs::AssetType &assetType, std::vector<std::string> *outNames) {
        std::map<std::string, std::shared_ptr<assets::Asset>>::iterator iterator;
        for (iterator = assetMap.begin(); iterator != assetMap.end(); ++iterator) {
            std::shared_ptr<assets::Asset> asset = iterator->second;
            structs::AssetInfo assetInfo = asset->GetAssetInfo();
            if (assetType != assetInfo.assetType) continue;

            std::string name = iterator->first;
            outNames->push_back(name);
        }

        std::sort(outNames->begin(), outNames->end(), utils::CompareStrings);
    }

    std::shared_ptr<assets::Asset> AssetManager::GetAssetRaw(const std::string &assetPath) {
        auto find = assetMap.find(assetPath);
        return ((find == assetMap.end()) ? nullptr : find->second);
    }

    std::string AssetManager::GetAssetPathRaw(const std::string &folderName, const std::string &assetName) {
        return (ASSET_FILE_PREFIX + folderName + "/" + assetName + ASSET_FILE_SUFFIX);
    }
}