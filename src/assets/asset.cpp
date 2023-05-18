#include <crossguid/guid.hpp>

#include "assets/asset.hpp"
#include "core/log.hpp"

namespace assets {
    int Asset::assetVersion = 1;

    Asset::Asset(structs::AssetType assetType) {
        auto guid = xg::newGuid();
        assetInfo = structs::AssetInfo{ assetType, guid.bytes() };
    }

    void Asset::WriteAssetInfo(std::fstream &file) {
        char *assetInfoBytes = new char[ASSET_INFO_BYTES];
        assetInfo.ToBytes(assetInfoBytes);
        file.write(assetInfoBytes, static_cast<long long>(ASSET_INFO_BYTES));
    }

    void Asset::ReadAssetInfo(std::fstream &file) {
        char *assetInfoBytes = new char[ASSET_INFO_BYTES];
        file.read(assetInfoBytes, static_cast<long long>(ASSET_INFO_BYTES));
        assetInfo = structs::AssetInfo::FromBytes(assetInfoBytes);
    }
}