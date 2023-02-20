#ifndef SENGINE_ENTITY_LOOP_RUNNER_H
#define SENGINE_ENTITY_LOOP_RUNNER_H

#include <queue>
#include <vector>
#include <memory>

#include "loop_runners/loop_runner.h"
#include "entity.h"

class EntityLoopRunner : public LoopRunner {
public:
    void AddEntity(const std::shared_ptr<Entity> &entity);

    void Update(double deltaTime) override;
    void Render() override;
private:
    std::vector<std::shared_ptr<Entity>> entities;
};

#endif //SENGINE_ENTITY_LOOP_RUNNER_H
