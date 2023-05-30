#ifndef SENGINE_ASSET_UTIL_TPP
#define SENGINE_ASSET_UTIL_TPP

#include "core/engine.hpp"
#include "utils/asset_util.hpp"
#include "managers/asset_manager.hpp"

namespace utils {
    template<typename T>
    enums::AssetType GetAssetType() {
        auto find = ASSET_ASSET_TYPES.find(typeid(T));
        if (find == ASSET_ASSET_TYPES.end()) core::Log::Error(fmt::format("asset type for typeid \"{}\" doesn't exist", typeid(T).name()));

        return find->second;
    }

    template<typename T>
    std::shared_ptr<T> GetAssetLock(const std::weak_ptr<T> &assetPtr) {
        if (auto lock = assetPtr.lock()) return lock;

        static auto assetManager = g_Engine->GetManager<managers::AssetManager>();
        auto defaultAsset = assetManager->GetDefaultAsset<T>();
        return defaultAsset.lock();
    }
}

#endif //SENGINE_ASSET_UTIL_TPP