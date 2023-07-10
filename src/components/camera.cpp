#include <glm/ext/matrix_transform.hpp>

#include "components/camera.hpp"
#include "core/entity.hpp"

namespace components {
    Camera::Camera(EntityId entityId) : targetPosition(0, 0, 0), fov(90.0f) {
        FetchEntity(entityId);
    }

    void Camera::Translate(glm::vec3 vector) {

    }

    void Camera::PostRender() {
        glm::vec3 position = entity->position;
        glm::mat4 view = glm::lookAt(position, (position + cameraFront), cameraUp);
    }
}