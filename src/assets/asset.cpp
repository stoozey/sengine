#include "assets/asset.h"

void Asset::WriteAssetInfo(SDL_RWops *file, AssetInfo &assetInfo) {
    SDL_RWwrite(file, reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo), 1);
}

void Asset::WriteAssetInfo(std::fstream &file, AssetInfo &assetInfo) {
    file.write(reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo));
}

AssetInfo Asset::ReadAssetInfo(SDL_RWops *file) {
    AssetInfo assetInfo{ };
    SDL_RWread(file, reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo), 1);
    return assetInfo;
}

AssetInfo Asset::ReadAssetInfo(std::fstream &file) {
    AssetInfo assetInfo{ };
    file.read(reinterpret_cast<char*>(&assetInfo), sizeof(AssetInfo));
    return assetInfo;
}