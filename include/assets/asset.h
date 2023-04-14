#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <SDL.h>

#include "structs/assets/asset_info.h"
#include "structs/assets/asset_type.h"
#include "structs/mesh.h"
#include "structs/texture.h"

namespace assets {
    class Asset {
    public:
        virtual void Save(const std::string &filePath) = 0;
        virtual void Load(const std::string &filePath) = 0;
    protected:
        static void WriteAssetInfo(SDL_RWops *file, structs::AssetInfo &assetInfo);
        static void WriteAssetInfo(std::fstream &file, structs::AssetInfo &assetInfo);

        static structs::AssetInfo ReadAssetInfo(SDL_RWops *file);
        static structs::AssetInfo ReadAssetInfo(std::fstream &file);
    private:
        std::vector<structs::Mesh> meshes;
    };
}

#endif //SENGINE_ASSET_H
