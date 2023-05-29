#ifndef SENGINE_LOOP_RUNNER_H
#define SENGINE_LOOP_RUNNER_H

namespace loopRunners {
    class LoopRunner {
    public:
        virtual ~LoopRunner();

        virtual void Update(double deltaTime) = 0;
        virtual void Render() = 0;
    };
}

#endif //SENGINE_LOOP_RUNNER_H
