#ifndef SENGINE_COMPONENT_H
#define SENGINE_COMPONENT_H

#include <memory>

#include "core/entity.fwd.hpp"

namespace components {
    class Component {
    public:
        Component();
        virtual ~Component();

        virtual void PreUpdate(double deltaTime);
        virtual void Update(double deltaTime);
        virtual void PostUpdate(double deltaTime);

        virtual void PreRender();
        virtual void Render();
        virtual void PostRender();
    protected:
        std::shared_ptr<core::Entity> entity;

        void FetchEntity(EntityId entityId);
    };
}

#endif //SENGINE_COMPONENT_H
