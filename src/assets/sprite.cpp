#include "assets/sprite.h"

Sprite::Sprite(const std::string& filePath, SDL_Renderer *sdlRenderer) : Asset(filePath) {
    renderer = ((sdlRenderer == nullptr) ? g_Engine->GetRenderer() : sdlRenderer);

    SDL_Surface *surface = IMG_Load(filePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

SDL_FRect Sprite::GetFRect(const Vector2 &position) {
    return { position.x, position.y, (float) width, (float) height };
}

void Sprite::Render(const Vector2 &position) {
    SDL_FRect rect = GetFRect(position);
    SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}