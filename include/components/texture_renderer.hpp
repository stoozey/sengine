#ifndef SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP
#define SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP

#include <utility>

#include "components/component.hpp"
#include "assets/texture.hpp"

namespace components {
    class TextureRenderer : public Component {
    public:
        TextureRenderer(EntityId entityId);
        ~TextureRenderer();

        void SetTexture(std::weak_ptr<assets::Texture> newTexture);

        void PostRender() override;
    private:
        std::weak_ptr<assets::Texture> texture;

        void RenderTexture();
    };
}

#endif //SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP
