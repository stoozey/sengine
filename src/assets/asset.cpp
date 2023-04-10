#include "assets/asset.h"

void Asset::WriteAssetInfo(SDL_RWops *file, AssetInfo &assetInfo) {
    SDL_RWwrite(file, reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo), 1);
}

AssetInfo Asset::ReadAssetInfo(SDL_RWops *file) {
    AssetInfo assetInfo{};
    SDL_RWread(file, reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo), 1);
    return assetInfo;
}