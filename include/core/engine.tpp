namespace core {
    template<typename T = loopRunners::LoopRunner>
    void Engine::AddLoopRunner(std::shared_ptr<T> &loopRunner) {
        loopRunners.emplace_back(loopRunner);
    }
}