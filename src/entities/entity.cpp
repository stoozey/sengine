#include "entity.h"

void Entity::Update(double deltaTime) {
    for (auto &component : components) {
        component.Update(deltaTime);
    }

    EntityUpdate(deltaTime);
}

void Entity::Render() {
    for (auto &component : components) {
        component.Render();
    }

    EntityRender();
}