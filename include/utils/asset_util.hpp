#ifndef SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP
#define SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP

#include "structs/assets/asset_type.hpp"
#include "assets/font.hpp"
#include "assets/material.hpp"
#include "assets/model.hpp"
#include "assets/shader.hpp"
#include "assets/sound.hpp"
#include "assets/texture.hpp"

namespace utils {
    template<typename T>
    structs::AssetType GetAssetType();
}

#include "asset_util.tpp"
#endif //SENGINE_ASSET_CREATOR_ASSET_UTIL_HPP
