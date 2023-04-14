#ifndef SENGINE_ENTITY_LOOP_RUNNER_H
#define SENGINE_ENTITY_LOOP_RUNNER_H

#include <queue>
#include <vector>
#include <memory>

#include "loop_runners/loop_runner.h"
#include "core/entity.h"

namespace loopRunners {
    class EntityLoopRunner : public LoopRunner {
    public:
        void AddEntity(std::shared_ptr<core::Entity> entity);

        void Update(double deltaTime) override;
        void Render() override;
    private:
        std::vector<std::shared_ptr<core::Entity>> entities;
    };
}

#endif //SENGINE_ENTITY_LOOP_RUNNER_H
