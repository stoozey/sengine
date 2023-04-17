#ifndef SENGINE_ENTITY_H
#define SENGINE_ENTITY_H

#include <vector>

#include "structs/vector3.hpp"
#include "components/component.hpp"

namespace core {
    class Entity {
    public:
        Entity();

        structs::Vector3 position;

        virtual void PreUpdate(double deltaTime);
        virtual void Update(double deltaTime);
        virtual void PostUpdate(double deltaTime);

        virtual void PreRender();
        virtual void Render();
        virtual void PostRender();
    };
}

#endif //SENGINE_ENTITY_H
