#ifndef SENGINE_ENTITY_LOOP_RUNNER_H
#define SENGINE_ENTITY_LOOP_RUNNER_H

#include <queue>
#include <vector>
#include <memory>
#include <unordered_map>

#include "loop_runners/loop_runner.hpp"
#include "core/entity.hpp"

namespace loopRunners {
    class EntityLoopRunner : public LoopRunner {
    public:
        EntityId AddEntity(std::unique_ptr<core::Entity> entity);

        template<typename T, typename... Args>
        EntityId CreateEntity(Args&&... args);

        template<typename T = core::Entity>
        std::weak_ptr<T> GetEntity(EntityId entityId);

        void DeleteEntity(EntityId entityId);

        void Update(double deltaTime) override;
        void Render() override;
    private:
        std::unordered_map<EntityId, std::shared_ptr<core::Entity>> entities;
    };
}

#include "loop_runners/entity_loop_runner.tpp"
#endif //SENGINE_ENTITY_LOOP_RUNNER_H
