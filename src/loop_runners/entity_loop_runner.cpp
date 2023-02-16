#include "loop_runners/entity_loop_runner.h"

void EntityLoopRunner::AddEntity(Entity *entity) {
    entities.emplace_back(entity);
}

void EntityLoopRunner::Update(double deltaTime) {
    for (auto &entity : entities) {
        entity->Update(deltaTime);
    }
}

void EntityLoopRunner::Render() {
    for (auto &entity : entities) {
        entity->Render();
    }
}