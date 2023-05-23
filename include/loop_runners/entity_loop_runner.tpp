#ifndef SENGINE_ASSET_CREATOR_ENTITY_LOOP_RUNNER_TPP
#define SENGINE_ASSET_CREATOR_ENTITY_LOOP_RUNNER_TPP

#include "loop_runners/entity_loop_runner.hpp"

namespace loopRunners {
    template<typename T, typename... Args>
    EntityId EntityLoopRunner::CreateEntity(Args&&... args) {
        std::unique_ptr<T> entity = std::make_unique<T>(std::forward<Args>(args)...);
        return AddEntity(std::move(entity));
    }

    template<typename T>
    std::weak_ptr<T> EntityLoopRunner::GetEntity(EntityId entityId) {
        auto find = entities.find(entityId);
        if (find == entities.end()) return std::weak_ptr<T>();

        return std::weak_ptr<T>(find->second);
    }
}

#endif //SENGINE_ASSET_CREATOR_ENTITY_LOOP_RUNNER_TPP
