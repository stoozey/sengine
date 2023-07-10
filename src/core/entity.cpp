#include "core/entity.hpp"
#include "utils/entity_util.hpp"

namespace core {
    EntityId Entity::Id = 0;

    Entity::Entity() : position({0, 0, 0}), id(Id++), frontVector(0.0f, 0.0f, -1.0f), upVector(0.0f, 1.0f, 0.0f) { }
    Entity::~Entity() { };

    void Entity::Move(const glm::vec2 &moveVector) {
        if (moveVector.x != 0) {
            position += (moveVector.x * glm::normalize(glm::cross(frontVector, upVector)));
        }

        if (moveVector.y != 0) {
            position += (moveVector.y * frontVector);
        }
    }

    EntityId Entity::GetEntityId() const {
        return id;
    }

    void Entity::PreUpdate(double deltaTime) {
        UpdateComponents(&components::Component::PreUpdate, deltaTime);
    }

    void Entity::Update(double deltaTime) {
        UpdateComponents(&components::Component::Update, deltaTime);
    }

    void Entity::PostUpdate(double deltaTime) {
        UpdateComponents(&components::Component::PostUpdate, deltaTime);
    }

    void Entity::PreRender() {
        RenderComponents(&components::Component::PreRender);
    }

    void Entity::Render() {
        RenderComponents(&components::Component::Render);
    }

    void Entity::PostRender() {
        RenderComponents(&components::Component::PostRender);
    }

    void Entity::UpdateComponents(void(components::Component::*func)(double), double deltaTime) {
        if (components.empty()) return;

        auto runner = utils::GetUpdateRunner<components::Component>(func);
        std::map<std::type_index, std::shared_ptr<components::Component>>::iterator iterator;
        for (iterator = components.begin(); iterator != components.end(); ++iterator) {
            std::shared_ptr<components::Component> component = iterator->second;
            runner(component.get(), deltaTime);
        }
    }

    void Entity::RenderComponents(void(components::Component::*func)()) {
        if (components.empty()) return;

        auto runner = utils::GetRenderRunner<components::Component>(func);
        std::map<std::type_index, std::shared_ptr<components::Component>>::iterator iterator;
        for (iterator = components.begin(); iterator != components.end(); ++iterator) {
            std::shared_ptr<components::Component> component = iterator->second;
            runner(component.get());
        }
    }
}