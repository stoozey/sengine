#ifndef SENGINE_SPRITE_H
#define SENGINE_SPRITE_H

#include <SDL.h>
#include <SDL_image.h>

#include "assets/asset.h"
#include "structs/vector2.h"

namespace assets {
    class Sprite : public Asset {
    public:
        Sprite(SDL_Renderer *sdlRenderer);
        static std::shared_ptr<Sprite> FromImage(SDL_Renderer *sdlRenderer, const std::string &filename);
        ~Sprite();

        void LoadImage(SDL_RWops *file);

        void Save(const std::string &filePath) override;
        void Load(const std::string &filePath) override;

        void Render(const structs::Vector2 &position);
        void SetRenderer(SDL_Renderer *renderer);

        SDL_FRect GetFRect(const structs::Vector2 &position);

        int GetWidth();
        int GetHeight();

    private:
        static structs::AssetInfo assetInfo;

        SDL_Renderer *renderer;
        SDL_Surface *surface;
        SDL_Texture *texture;

        int width;
        int height;
    };
}

#endif //SENGINE_SPRITE_H
