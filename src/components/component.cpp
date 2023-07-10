#include "core/log.hpp"
#include "components/component.hpp"
#include "loop_runners/entity_loop_runner.hpp"
#include "core/engine.hpp"

namespace components {
    Component::Component() { }
    Component::~Component() { }

    void Component::PreUpdate(double deltaTime) { }
    void Component::Update(double deltaTime) { }
    void Component::PostUpdate(double deltaTime) { }

    void Component::PreRender() { }
    void Component::Render() { }
    void Component::PostRender() { }

    void Component::FetchEntity(EntityId entityId) {
        auto entityLoopRunner = g_Engine->GetLoopRunner<loopRunners::EntityLoopRunner>();
        auto weakEntity = entityLoopRunner->GetEntity(entityId);
        if (auto lock = weakEntity.lock()) {
            entity = lock;
        } else {
            core::Log::Error(fmt::format("entity of id %s doesn't exist", entityId));
        }
    }
}