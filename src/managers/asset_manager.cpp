#include <filesystem>

#include "managers/asset_manager.h"
#include "assets/sprite.h"
#include "assets/shader.h"
#include "assets/model.h"
#include "assets/texture.h"
#include "structs/assets/asset_type.h"
#include "structs/assets/asset_path.h"

managers::AssetManager *g_AssetManager = new managers::AssetManager();

namespace managers {
    std::map<std::string, assets::Asset *> AssetManager::assets = std::map<std::string, assets::Asset*>();

    assets::Asset *AssetManager::LoadAsset(structs::AssetPath &assetPath) {
        const std::string path = assetPath.GetFullPath();
        assets::Asset *asset = GetAsset(assetPath);
        if ((std::filesystem::exists(path)) && (asset == nullptr))
        {
            switch (assetPath.assetType)
            {
                case structs::AssetType::Sprite:
                {
                    asset = new assets::Sprite(nullptr);
                    break;
                }

                case structs::AssetType::Shader:
                {
                    asset = new assets::Shader();
                    break;
                }

                case structs::AssetType::Model:
                {
                    asset = new assets::Model();
                    break;
                }

                case structs::AssetType::Texture:
                {
                    asset = new assets::Texture();
                    break;
                }
            }

            asset->Load(path);
            assets.insert({path, asset});
        }

        return asset;
    }

    void AssetManager::UnLoadAsset(structs::AssetPath &assetPath) {
        const std::string path = assetPath.GetFullPath();
        auto find = assets.find(path);
        if (find == assets.end()) return;

        assets.erase(find);
        delete find->second;
    }

    assets::Asset *AssetManager::GetAsset(structs::AssetPath &assetPath) {
        const std::string path = assetPath.GetFullPath();
        auto find = assets.find(path);
        return ((find == assets.end()) ? nullptr : find->second);
    }

    bool AssetManager::AssetExists(structs::AssetPath &assetPath) {
        return (GetAsset(assetPath) != nullptr);
    }
}