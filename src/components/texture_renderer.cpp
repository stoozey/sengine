#include "components/texture_renderer.hpp"
#include "core/log.hpp"

namespace components {
    TextureRenderer::TextureRenderer(EntityId id){
        core::Log::Info("texture renderer created!!!!!!!!!!!");
        FetchEntity(id);
    }

    TextureRenderer::~TextureRenderer() { }

    void TextureRenderer::PostRender() {
        RenderTexture();
    }

    void TextureRenderer::RenderTexture() {
        core::Log::Info("texture rendere rednerererr!!!");
    }
}