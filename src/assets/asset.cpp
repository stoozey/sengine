#include <crossguid/guid.hpp>

#include "assets/asset.hpp"
#include "core/log.hpp"

namespace assets {
    const size_t ASSET_INFO_SIZE = sizeof(structs::AssetInfo);

    int Asset::assetVersion = 1;

    Asset::Asset(structs::AssetType assetType) {
        auto guid = xg::newGuid();
        assetInfo = structs::AssetInfo{ assetType, guid.str().c_str() };
    }

    void Asset::WriteAssetInfo(std::fstream &file, structs::AssetInfo &assetInfo) {
        file.write(reinterpret_cast<char *>(&assetVersion), sizeof(int));
        file.write(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
    }

    structs::AssetInfo Asset::ReadAssetInfo(std::fstream &file) {
        int readAssetVersion;
        file.read(reinterpret_cast<char *>(&readAssetVersion), sizeof(int));

        if (readAssetVersion != assetVersion) core::Log::Error("asset version mismatch (read: {}, expected: {})", readAssetVersion, assetVersion);

        structs::AssetInfo assetInfo{ };
        file.read(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
        return assetInfo;
    }
}