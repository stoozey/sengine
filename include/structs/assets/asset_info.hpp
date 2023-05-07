#ifndef SENGINE_TEST1_ASSET_INFO_H
#define SENGINE_TEST1_ASSET_INFO_H

#include "structs/assets/asset_type.hpp"

namespace structs {
    const short ASSET_INFO_GUID_BYTES = 36;

    struct AssetInfo {
        AssetType assetType;
        const char *guid[ASSET_INFO_GUID_BYTES];
    };
}

#endif //SENGINE_TEST1_ASSET_INFO_H
