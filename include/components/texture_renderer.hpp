#ifndef SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP
#define SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP

#include "components/component.hpp"

namespace components {
    class TextureRenderer : public Component {
    public:
        TextureRenderer(EntityId entityId);
        ~TextureRenderer();

        void PostRender() override;

    private:
        void RenderTexture();
    };
}

#endif //SENGINE_ASSET_CREATOR_TEXTURE_RENDERER_HPP
