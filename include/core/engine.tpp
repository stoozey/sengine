#ifndef SENGINE_ENGINE_TPP
#define SENGINE_ENGINE_TPP

namespace core {
    template<typename T = loopRunners::LoopRunner>
    void Engine::AddLoopRunner(std::shared_ptr<T> &loopRunner) {
        loopRunners.emplace_back(loopRunner);
    }
}

#endif // SENGINE_ENGINE_TPP