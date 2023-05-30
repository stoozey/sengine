#ifndef SENGINE_ENTITY_H
#define SENGINE_ENTITY_H

#include <vector>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <glm/glm.hpp>

#include "components/component.hpp"
#include "structs/vector3.hpp"

typedef unsigned long EntityId;

namespace core {
    class Entity {
    public:
        Entity();
        virtual ~Entity();

        glm::vec3 position;

        EntityId GetEntityId() const;

        template<typename T>
        bool HasComponent();

        template<typename T>
        void AddComponent();

        template<typename T>
        std::shared_ptr<T> GetComponent();

        virtual void PreUpdate(double deltaTime);
        virtual void Update(double deltaTime);
        virtual void PostUpdate(double deltaTime);

        virtual void PreRender();
        virtual void Render();
        virtual void PostRender();
    protected:


        void UpdateComponents(void(components::Component::*func)(double), double deltaTime);
        void RenderComponents(void(components::Component::*func)());
    private:
        static EntityId Id;

        EntityId id;
        std::map<std::type_index, std::shared_ptr<components::Component>> components;
    };
}

#include "core/entity.tpp"
#endif //SENGINE_ENTITY_H
