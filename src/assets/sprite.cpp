#include "assets/sprite.h"

Sprite::Sprite(SDL_Renderer *sdlRenderer) {
    renderer = ((sdlRenderer == nullptr) ? g_Engine->GetRenderer() : sdlRenderer);
    texture = nullptr;
    width = 0;
    height = 0;
}

Sprite::~Sprite() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Load(const std::string &filePath) {
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

void Sprite::SetRenderer(SDL_Renderer *sdlRenderer) {
    renderer = sdlRenderer;
}

SDL_FRect Sprite::GetFRect(const Vector2 &position) {
    return { position.x, position.y, (float) width, (float) height };
}

int Sprite::GetWidth() {
    return width;
}

int Sprite::GetHeight() {
    return height;
}

void Sprite::Render(const Vector2 &position) {
    if (!texture) return;

    SDL_FRect rect = GetFRect(position);
    SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}