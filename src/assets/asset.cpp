#include "assets/asset.hpp"

namespace assets {
    const size_t ASSET_INFO_SIZE = sizeof(structs::AssetInfo);

    void Asset::WriteAssetInfo(SDL_RWops *file, structs::AssetInfo &assetInfo) {
        SDL_RWwrite(file, reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE, 1);
    }

    void Asset::WriteAssetInfo(std::fstream &file, structs::AssetInfo &assetInfo) {
        file.write(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
    }

    structs::AssetInfo Asset::ReadAssetInfo(SDL_RWops *file) {
        structs::AssetInfo assetInfo{ };
        SDL_RWread(file, reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE, 1);
        return assetInfo;
    }

    structs::AssetInfo Asset::ReadAssetInfo(std::fstream &file) {
        structs::AssetInfo assetInfo{ };
        file.read(reinterpret_cast<char *>(&assetInfo), ASSET_INFO_SIZE);
        return assetInfo;
    }
}