#include "loop_runners/entity_loop_runner.hpp"
#include "exceptions/not_implemented.hpp"

namespace loopRunners {
    EntityId EntityLoopRunner::AddEntity(std::unique_ptr<core::Entity> entity) {
        EntityId entityId = entity->GetEntityId();
        entities[entityId] = std::move(entity);

        return entityId;
    }

    void EntityLoopRunner::DeleteEntity(EntityId entityId) {
        throw exceptions::NotImplemented();
    }

    void EntityLoopRunner::Update(double deltaTime) {
        for (auto &find : entities) {
            find.second->PreUpdate(deltaTime);
        }

        for (auto &find : entities) {
            find.second->Update(deltaTime);
        }

        for (auto &find : entities) {
            find.second->PostUpdate(deltaTime);
        }
    }

    void EntityLoopRunner::Render() {
        for (auto &find : entities) {
            find.second->PreRender();
        }

        for (auto &find : entities) {
            find.second->Render();
        }

        for (auto &find : entities) {
            find.second->PostRender();
        }
    }
}