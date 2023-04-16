#include "loop_runners/entity_loop_runner.hpp"

namespace loopRunners {
    void EntityLoopRunner::Update(double deltaTime) {
        for (auto &entity: entities)
        {
            entity->PreUpdate(deltaTime);
        }

        for (auto &entity: entities)
        {
            entity->Update(deltaTime);
        }

        for (auto &entity: entities)
        {
            entity->PostUpdate(deltaTime);
        }
    }

    void EntityLoopRunner::Render() {
        for (auto &entity: entities)
        {
            entity->PreRender();
        }

        for (auto &entity: entities)
        {
            entity->Render();
        }

        for (auto &entity: entities)
        {
            entity->PostRender();
        }
    }
}