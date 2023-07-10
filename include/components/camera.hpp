#ifndef SENGINE_JUMP_KING_CAMERA_HPP
#define SENGINE_JUMP_KING_CAMERA_HPP

#include <glm/glm.hpp>

#include "components/component.hpp"

namespace components {
    class Camera : public Component {
    public:
        Camera(EntityId entityId);

        void PostRender() override;

        void Translate(glm::vec3 vector);
    private:
        glm::vec3 targetPosition;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        float fov;
    };
}

#endif //SENGINE_JUMP_KING_CAMERA_HPP
