#ifndef SENGINE_ASSET_CREATOR_ENTITY_UTIL_TPP
#define SENGINE_ASSET_CREATOR_ENTITY_UTIL_TPP

#include "utils/entity_util.hpp"

namespace utils {
    template<typename T>
    std::function<void(T*, double)> GetUpdateRunner(void(T::*update)(double)) {
        return [update](T *entity, double deltaTime) {
            (entity->*update)(deltaTime);
        };
    }

    template<typename T>
    std::function<void(T*)> GetRenderRunner(void(T::*render)()) {
        return [render](T *entity) {
            (entity->*render)();
        };
    }
}

#endif //SENGINE_ASSET_CREATOR_ENTITY_UTIL_TPP
