#ifndef SENGINE_SPRITE_H
#define SENGINE_SPRITE_H

#include <SDL.h>

#include "engine.h"
#include "assets/asset.h"

class Sprite : public Asset {
public:
    Sprite(const std::string& filePath, SDL_Renderer *sdlRenderer);
private:
    SDL_Renderer *renderer;
};

#endif //SENGINE_SPRITE_H
