#ifndef SENGINE_ASSET_H
#define SENGINE_ASSET_H

#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <SDL.h>
#include <crossguid/guid.hpp>

#include "structs/asset_info.hpp"
#include "enums/asset_type.hpp"

namespace assets {
    class Asset {
    public:
        explicit Asset(enums::AssetType assetType);
        virtual ~Asset();

        virtual void Save(const std::string &filePath) = 0;
        virtual void Load(const std::string &filePath) = 0;

        structs::AssetInfo GetAssetInfo();
        xg::Guid GetGuid();
    protected:
        void WriteAssetInfo(std::fstream &file);
        void ReadAssetInfo(std::fstream &file);

        structs::AssetInfo assetInfo;
    private:
        static int assetVersion;
    };
}

#endif //SENGINE_ASSET_H
