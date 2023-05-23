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
            core::Log::Warn("tried to add loop runner \"{}\", but it already exists", typeid(T).name());
        }

        return GetLoopRunner<T>();
    }

    template<typename T>
    T *Engine::GetLoopRunner() {
        T *loopRunner = nullptr;
        auto find = loopRunners.find(typeid(T));
        if (find != loopRunners.end()) {
            loopRunner = static_cast<T*>(find->second.get());
        }

        return loopRunner;
    }

    template<typename T>
    T *Engine::AddManager() {
        auto find = managers.find(typeid(T));
        if (find == managers.end()) {
            managers[typeid(T)] = std::make_unique<T>();
        } else {
            core::Log::Warn("tried to add manager \"{}\", but it already exists", typeid(T).name());
        }

        return GetManager<T>();
    }

    template<typename T>
    T *Engine::GetManager() {
        T *manager = nullptr;
        auto find = managers.find(typeid(T));
        if (find != managers.end()) {
            manager = static_cast<T*>(find->second.get());
        }

        return manager;
    }
}

#endif // SENGINE_ENGINE_TPP