#ifndef SENGINE_ENGINE_TPP
#define SENGINE_ENGINE_TPP

#include "core/engine.hpp"
#include "core/log.hpp"

namespace core {
    template<typename T>
    T *Engine::AddLoopRunner() {
        auto find = loopRunners.find(typeid(T));
        if (find == loopRunners.end()) {
            loopRunners[typeid(T)] = std::make_unique<T>();
        } else {
            core::Log::Warn(fmt::format("tried to add loop runner \"{}\", but it already exists", typeid(T).name()));
        }

        return GetLoopRunner<T>();
    }

    template<typename T>
    T *Engine::GetLoopRunner(bool suppressNotAddedWarning) {
        T *loopRunner = nullptr;
        auto find = loopRunners.find(typeid(T));
        if (find != loopRunners.end()) {
            loopRunner = static_cast<T*>(find->second.get());
        } else if (!suppressNotAddedWarning) {
            core::Log::Warn(fmt::format("tried to get loop runner \"{}\" which hasn't been added", typeid(T).name()));
        }

        return loopRunner;
    }

    template<typename T>
    T *Engine::AddManager() {
        auto find = managers.find(typeid(T));
        if (find == managers.end()) {
            managers[typeid(T)] = std::make_unique<T>();
        } else {
            core::Log::Warn(fmt::format("tried to add manager \"{}\", but it already exists", typeid(T).name()));
        }

        return GetManager<T>();
    }

    template<typename T>
    T *Engine::GetManager(bool suppressNotAddedWarning) {
        T *manager = nullptr;
        auto find = managers.find(typeid(T));
        if (find != managers.end()) {
            manager = static_cast<T*>(find->second.get());
        } else if (!suppressNotAddedWarning) {
            core::Log::Warn(fmt::format("tried to get manager \"{}\" which hasn't been added", typeid(T).name()));
        }

        return manager;
    }
}

#endif // SENGINE_ENGINE_TPP