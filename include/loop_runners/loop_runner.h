#ifndef SENGINE_LOOP_RUNNER_H
#define SENGINE_LOOP_RUNNER_H

enum class LoopRunnerType {
    Entity
};

class LoopRunner {
public:
    LoopRunnerType GetLoopRunnerType();

    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
protected:
    LoopRunnerType loopRunnerType = LoopRunnerType::Entity;
};

#endif //SENGINE_LOOP_RUNNER_H
