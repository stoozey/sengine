#ifndef SENGINE_ENTITY_H
#define SENGINE_ENTITY_H

#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>

#include "components/component.hpp"
#include "structs/vector3.hpp"

typedef unsigned long EntityId;

namespace core {
    class Entity {
    public:
        Entity();
        virtual ~Entity();

        structs::Vector3 position;

        EntityId GetEntityId() const;

        virtual void PreUpdate(double deltaTime);
        virtual void Update(double deltaTime);
        virtual void PostUpdate(double deltaTime);

        virtual void PreRender();
        virtual void Render();
        virtual void PostRender();
    private:
        static EntityId Id;

        EntityId id;
        std::map<std::type_info, components::Component> components;
    };
}

#endif //SENGINE_ENTITY_H
