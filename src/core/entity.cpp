#include "core/entity.hpp"

namespace core {
    EntityId Entity::Id = 0;

    Entity::Entity() : position({0, 0, 0}), id(Id++) { }
    Entity::~Entity() { };

    EntityId Entity::GetEntityId() const {
        return id;
    }

    void Entity::PreUpdate(double deltaTime) { }
    void Entity::Update(double deltaTime) { }
    void Entity::PostUpdate(double deltaTime) { }

    void Entity::PreRender() { }
    void Entity::Render() { }
    void Entity::PostRender() { }
}