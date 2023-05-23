#include "loop_runners/loop_runner.hpp"
#include "structs/loop_runners/loop_runner_type.hpp"

namespace loopRunners {
    LoopRunner::~LoopRunner() { };

    structs::LoopRunnerType LoopRunner::GetLoopRunnerType() {
        return loopRunnerType;
    }
}