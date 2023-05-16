#ifndef SENGINE_TEST1_ASSET_INFO_H
#define SENGINE_TEST1_ASSET_INFO_H

#include <crossguid/guid.hpp>

#include "structs/assets/asset_type.hpp"

namespace structs {
    const short ASSET_INFO_GUID_BYTES = 36;

    struct AssetInfo {
        AssetType assetType;
        std::array<unsigned char, 16> guid;

        xg::Guid GetGuid() {
            return xg::Guid(guid);
        }
    };
}

#endif //SENGINE_TEST1_ASSET_INFO_H
