#include "entity.h"

Entity::Entity() {
    position = {0, 0};
}

void Entity::PreUpdate(double deltaTime) { }
void Entity::Update(double deltaTime) { }
void Entity::PostUpdate(double deltaTime) { }

void Entity::PreRender() { }
void Entity::Render() { }
void Entity::PostRender() { }