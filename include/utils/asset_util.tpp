#ifndef SENGINE_ASSET_UTIL_TPP
#define SENGINE_ASSET_UTIL_TPP

namespace utils {
    template<>
    structs::AssetType GetAssetType<assets::Font>() {
        return structs::AssetType::Font;
    }

    template<>
    structs::AssetType GetAssetType<assets::Material>() {
        return structs::AssetType::Material;
    }

    template<>
    structs::AssetType GetAssetType<assets::Model>() {
        return structs::AssetType::Model;
    }

    template<>
    structs::AssetType GetAssetType<assets::Shader>() {
        return structs::AssetType::Shader;
    }

    template<>
    structs::AssetType GetAssetType<assets::Sound>() {
        return structs::AssetType::Sound;
    }

    template<>
    structs::AssetType GetAssetType<assets::Texture>() {
        return structs::AssetType::Texture;
    }
}

#endif //SENGINE_ASSET_UTIL_TPP