#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <SDL.h>

#include "datatypes/asset_info.h"
#include "datatypes/asset_type.h"
#include "datatypes/mesh.h"
#include "datatypes/texture.h"

class Asset {
public:
    virtual void Save(const std::string &filePath) = 0;
    virtual void Load(const std::string &filePath) = 0;
protected:
    static void WriteAssetInfo(SDL_RWops *file, AssetInfo &assetInfo);
    static void WriteAssetInfo(std::fstream &file, AssetInfo &assetInfo);

    static AssetInfo ReadAssetInfo(SDL_RWops *file);
    static AssetInfo ReadAssetInfo(std::fstream &file);
private:
    std::vector<Mesh> meshes;
};

#endif //SENGINE_ASSET_H
