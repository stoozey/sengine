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
        entity = entityLoopRunner->GetEntity(entityId);
    }
}