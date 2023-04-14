#include <iostream>

#include "assets/sprite.h"
#include "structs/assets/asset_info.h"
#include "structs/assets/asset_type.h"
#include "core/engine.h"

namespace assets {
    structs::AssetInfo Sprite::assetInfo{structs::AssetType::Sprite};

    Sprite::Sprite(SDL_Renderer *sdlRenderer) {
        renderer = ((sdlRenderer == nullptr) ? g_Engine->GetRenderer() : sdlRenderer);
        surface = nullptr;
        texture = nullptr;
        width = 0;
        height = 0;
    }

    std::shared_ptr<Sprite> Sprite::FromImage(SDL_Renderer *sdlRenderer, const std::string &filename) {
        std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(sdlRenderer);
        SDL_RWops *file = SDL_RWFromFile(filename.c_str(), "r");
        sprite->LoadImage(file);
        SDL_RWclose(file);

        return sprite;
    }

    Sprite::~Sprite() {
        if (texture)
        {
            SDL_DestroyTexture(texture);
        }

        if (surface)
        {
            SDL_FreeSurface(surface);
        }
    }

    void Sprite::LoadImage(SDL_RWops *file) {
        surface = IMG_Load_RW(file, 0);
        texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    }

    void Sprite::Save(const std::string &filePath) {
        SDL_RWops *file = SDL_RWFromFile(filePath.c_str(), "w");
        WriteAssetInfo(file, assetInfo);

        IMG_SavePNG_RW(surface, file, 0);
        SDL_RWclose(file);
    }

    void Sprite::Load(const std::string &filePath) {
        SDL_RWops *file = SDL_RWFromFile(filePath.c_str(), "r");
        std::cout << "read asset info " << file->type << std::endl;
        ReadAssetInfo(file);

        LoadImage(file);
        SDL_RWclose(file);
    }

    void Sprite::SetRenderer(SDL_Renderer *sdlRenderer) {
        renderer = sdlRenderer;
    }

    SDL_FRect Sprite::GetFRect(const structs::Vector2 &position) {
        return {position.x, position.y, (float) width, (float) height};
    }

    int Sprite::GetWidth() {
        return width;
    }

    int Sprite::GetHeight() {
        return height;
    }

    void Sprite::Render(const structs::Vector2 &position) {
        if (!texture) return;

        SDL_FRect rect = GetFRect(position);
        SDL_RenderCopyF(renderer, texture, nullptr, &rect);
    }
}