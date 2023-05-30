#ifndef SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP
#define SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP

#include <typeindex>
#include <typeinfo>

#include "enums/asset_type.hpp"
#include "assets/asset.hpp"
#include "assets/font.hpp"
#include "assets/material.hpp"
#include "assets/model.hpp"
#include "assets/shader.hpp"
#include "assets/sound.hpp"
#include "assets/texture.hpp"

const std::unordered_map<std::type_index, enums::AssetType> ASSET_ASSET_TYPES = {
        { typeid(assets::Font), enums::AssetType::Font },
        { typeid(assets::Material), enums::AssetType::Material },
        { typeid(assets::Model), enums::AssetType::Model },
        { typeid(assets::Shader), enums::AssetType::Shader },
        { typeid(assets::Sound), enums::AssetType::Sound },
        { typeid(assets::Texture), enums::AssetType::Texture }
};

namespace utils {
    template<typename T>
    enums::AssetType GetAssetType();

    template<typename T>
    std::shared_ptr<T> GetAssetLock(const std::weak_ptr<T> &assetPtr);

    template<typename T = assets::Asset>
    void GetAssetNames(std::vector<std::string> *outNames);
    void GetAssetNames(const enums::AssetType &assetType, std::vector<std::string> *outNames);
}

#include "asset_util.tpp"
#endif //SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP
