#ifndef SENGINE_ASSET_CREATOR_ENTITY_TPP
#define SENGINE_ASSET_CREATOR_ENTITY_TPP

#include <fmt/format.h>

#include "core/entity.hpp"
#include "core/log.hpp"
#include "exceptions/invalid_template.hpp"

namespace core {
    template<typename T>
    bool Entity::HasComponent() {
        return (components.find(typeid(T)) != components.end());
    }

    template<typename T>
    void Entity::AddComponent() {
        if (HasComponent<T>()) return core::Log::Warn(fmt::format("tried to add component \"{}\", but it already exists", typeid(T).name()));

        std::shared_ptr<T> component = std::make_shared<T>(id);
        components[typeid(T)] = std::static_pointer_cast<components::Component>(component);
    }

    template<typename T>
    std::shared_ptr<T> Entity::GetComponent() {
        if (!HasComponent<T>()) throw exceptions::InvalidTemplate(fmt::format("entity {} not have a \"{}\" component", id, typeid(T).name()));

        auto find = components.find(typeid(T));
        return std::static_pointer_cast<T>(find->second);
    }
}

#endif //SENGINE_ASSET_CREATOR_ENTITY_TPP
