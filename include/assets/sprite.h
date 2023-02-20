#ifndef SENGINE_SPRITE_H
#define SENGINE_SPRITE_H

#include <SDL.h>
#include <SDL_image.h>

#include "engine.h"
#include "assets/asset.h"
#include "datatypes/vector2.h"

class Sprite : public Asset {
public:
    Sprite(SDL_Renderer *sdlRenderer);
    ~Sprite();

    void Load(const std::string& filePath) override;

    void Render(const Vector2 &position);

    void SetRenderer(SDL_Renderer *renderer);

    SDL_FRect GetFRect(const Vector2 &position);
    int GetWidth();
    int GetHeight();
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    int width;
    int height;
};

#endif //SENGINE_SPRITE_H
