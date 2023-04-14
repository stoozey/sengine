#ifndef SENGINE_LOOP_RUNNER_H
#define SENGINE_LOOP_RUNNER_H

#include "structs/loop_runners/loop_runner_type.h"

namespace loopRunners {
    class LoopRunner {
    public:
        structs::LoopRunnerType GetLoopRunnerType();

        virtual void Update(double deltaTime) = 0;

        virtual void Render() = 0;

    protected:
        structs::LoopRunnerType loopRunnerType = structs::LoopRunnerType::Entity;
    };
}

#endif //SENGINE_LOOP_RUNNER_H
