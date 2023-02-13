#ifndef SENGINE_LOOP_RUNNER_H
#define SENGINE_LOOP_RUNNER_H

enum class LoopRunnerType {
    Entity
};

class LoopRunner {
public:
    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;

    LoopRunnerType GetLoopRunnerType();
protected:
    LoopRunnerType loopRunnerType;
};

#endif //SENGINE_LOOP_RUNNER_H
