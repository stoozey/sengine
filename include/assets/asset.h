#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>
#include <SDL.h>

#include "datatypes/asset_info.h"
#include "datatypes/asset_type.h"

class Asset {
public:
    virtual void Save(const std::string &filePath) = 0;
    virtual void Load(const std::string &filePath) = 0;

protected:
    static void WriteAssetInfo(SDL_RWops *file, AssetInfo &assetInfo);
    static AssetInfo ReadAssetInfo(SDL_RWops *file);
};

#endif //SENGINE_ASSET_H
