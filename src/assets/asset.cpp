#include <crossguid/guid.hpp>

#include "assets/asset.hpp"
#include "core/log.hpp"

namespace assets {
    const char *ASSET_FILE_SIGNATURE = "ASSET";
    const size_t ASSET_INFO_SIZE = sizeof(structs::AssetInfo);

    int Asset::assetVersion = 1;

    Asset::Asset(structs::AssetType assetType) {
        auto guid = xg::newGuid();
        assetInfo = structs::AssetInfo{ assetType, guid.bytes() };
    }

    void Asset::WriteAssetInfo(std::fstream &file) {
        file << ASSET_FILE_SIGNATURE;
        file.write(reinterpret_cast<char *>(&assetVersion), sizeof(int));
        file.write(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
    }

    void Asset::ReadAssetInfo(std::fstream &file) {
        std::streamsize signatureLength = std::strlen(ASSET_FILE_SIGNATURE);
        char *signature = new char[signatureLength + 1];

        file.read(signature, signatureLength);
        signature[signatureLength] = '\0';
        if (std::strcmp(signature, ASSET_FILE_SIGNATURE) != 0) core::Log::Error("invalid file type (got {}, wanted {})", signature, ASSET_FILE_SIGNATURE);

        int readAssetVersion;
        file.read(reinterpret_cast<char *>(&readAssetVersion), sizeof(int));
        if (readAssetVersion != assetVersion) core::Log::Error("asset version mismatch (read: {}, expected: {})", readAssetVersion, assetVersion);

        file.read(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
        xg::Guid guid = xg::Guid(assetInfo.guid);
    }
}