#include "components/texture_renderer.hpp"
#include "core/log.hpp"

namespace components {
    TextureRenderer::TextureRenderer(EntityId id){
        core::Log::Info("texture renderer created!!!!!!!!!!!");
        FetchEntity(id);
    }

    TextureRenderer::~TextureRenderer() { }

    void TextureRenderer::SetTexture(std::weak_ptr<assets::Texture> newTexture) {
        texture = newTexture;
    }

    void TextureRenderer::PostRender() {
    }

    void TextureRenderer::RenderTexture() {
        core::Log::Info("texture rendere rednerererr!!!");

    }
}