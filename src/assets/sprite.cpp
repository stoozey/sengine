#include "assets/sprite.h"

Sprite::Sprite(const std::string& filePath, SDL_Renderer *sdlRenderer) : Asset(filePath) {
    renderer = ((sdlRenderer == nullptr) ? g_Engine->GetRenderer() : sdlRenderer);

}