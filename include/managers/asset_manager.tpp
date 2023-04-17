namespace managers {
    template<typename T = assets::Asset>
    std::shared_ptr<T> AssetManager::LoadAsset(const std::string &assetName) {
        const std::string assetPath = GetAssetPath<T>(assetName);
        auto asset = GetAsset<T>(assetName);
        if ((std::filesystem::exists(assetPath)) && (asset == nullptr)) {
            asset = std::make_shared<T>();
            asset->Load(assetPath);
            assets.insert({ assetPath, asset });
        }

        if (asset == nullptr) {
            const std::string defaultAssetPath = GetAssetPath<T>(ASSET_DEFAULT_NAME);
            spdlog::warn("asset \"" + assetPath + "\" not found, using default");
            if (!std::filesystem::exists(defaultAssetPath)) {
                spdlog::critical("missing default asset \"" + defaultAssetPath + "\"");
                throw;
            }

            asset = LoadAsset<T>(ASSET_DEFAULT_NAME);
        }

        return asset;
    }

    template<typename T = assets::Asset>
    void AssetManager::UnLoadAsset(const std::string &assetName) {
        const std::string assetPath = GetAssetPath<T>(assetName);
        auto find = assets.find(assetPath);
        if (find == assets.end()) return;

        assets.erase(find);
    }

    template<typename T = assets::Asset>
    std::shared_ptr<T> AssetManager::GetAsset(const std::string &assetName) {
        const std::string assetPath = GetAssetPath<T>(assetName);
        auto find = assets.find(assetPath);
        return dynamic_pointer_cast<T>(((find == assets.end()) ? nullptr : find->second));
    }

    template<typename T = assets::Asset>
    bool AssetManager::AssetExists(const std::string &assetName) {
        return (GetAsset<T>(assetName) != nullptr);
    }

    template<typename T = assets::Asset>
    std::shared_ptr<T> AssetManager::GetDefaultAsset() {
        return LoadAsset<T>(".default");
    };
}