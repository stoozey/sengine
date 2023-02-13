#ifndef SENGINE_ENTITY_LOOP_RUNNER_H
#define SENGINE_ENTITY_LOOP_RUNNER_H

#include <queue>
#include <vector>

#include "loop_runners/loop_runner.h"
#include "entity.h"

class Compare
{
public:
    bool operator() (Entity *a, Entity *b) {
        return (a->position.z > b->position.z);
    }
};

class EntityLoopRunner : public LoopRunner {
public:
    EntityLoopRunner();

    void AddEntity(Entity *entity);

    void Update(double deltaTime);
    void Render();
private:
    std::vector<Entity*> entities;
};

#endif //SENGINE_ENTITY_LOOP_RUNNER_H
