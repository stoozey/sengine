#ifndef SENGINE_ASSET_UTIL_TPP
#define SENGINE_ASSET_UTIL_TPP

#include "utils/asset_util.hpp"

namespace utils {
    template<typename T>
    enums::AssetType GetAssetType() {
        auto find = ASSET_ASSET_TYPES.find(typeid(T));
        if (find == ASSET_ASSET_TYPES.end()) core::Log::Error(fmt::format("asset type for typeid \"{}\" doesn't exist", typeid(T).name()));

        return find->second;
    }
}

#endif //SENGINE_ASSET_UTIL_TPP