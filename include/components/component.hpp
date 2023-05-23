#ifndef SENGINE_COMPONENT_H
#define SENGINE_COMPONENT_H

#include <memory>

#include "core/entity.fwd.hpp"

namespace components {
    class Component {
    public:
        explicit Component(EntityId entityId);

        virtual void Update(double deltaTime);
        virtual void Render();
    protected:
        std::weak_ptr<core::Entity> entity;
    };
}

#endif //SENGINE_COMPONENT_H
