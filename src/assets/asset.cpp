#include <crossguid/guid.hpp>

#include "assets/asset.hpp"
#include "core/log.hpp"

namespace assets {
    int Asset::assetVersion = 1;

    Asset::Asset(enums::AssetType assetType) : assetInfo() {
        auto guid = xg::newGuid();
        assetInfo = structs::AssetInfo{ assetType, guid.bytes() };
    }

    Asset::~Asset() { }

    structs::AssetInfo Asset::GetAssetInfo() {
        return assetInfo;
    }

    xg::Guid Asset::GetGuid() {
        return assetInfo.GetGuid();
    }

    void Asset::WriteAssetInfo(std::fstream &file) {
        char *assetInfoBytes = new char[ASSET_INFO_BYTES];
        assetInfo.ToBytes(assetInfoBytes);
        file.write(assetInfoBytes, static_cast<long long>(ASSET_INFO_BYTES));

        delete[] assetInfoBytes;
    }

    void Asset::ReadAssetInfo(std::fstream &file) {
        char *assetInfoBytes = new char[ASSET_INFO_BYTES];
        file.read(assetInfoBytes, static_cast<long long>(ASSET_INFO_BYTES));
        assetInfo = structs::AssetInfo::FromBytes(assetInfoBytes);
        delete[] assetInfoBytes;
    }
}