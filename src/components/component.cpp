#include "components/component.hpp"
#include "loop_runners/entity_loop_runner.hpp"
#include "core/engine.hpp"

namespace components {
    Component::Component(EntityId entityId) {
        auto entityLoopRunner = g_Engine->GetLoopRunner<loopRunners::EntityLoopRunner>();
        entity = entityLoopRunner->GetEntity(entityId);
    }

    void Component::Update(double deltaTime) { }
    void Component::Render() { }
}