#ifndef SENGINE_ENTITY_H
#define SENGINE_ENTITY_H

#include <vector>

#include "datatypes/vector3.h"
#include "components/component.h"

class Entity {
public:
    Vector3 position;

    void Update(double deltaTime);
    void Render();
protected:
    std::vector<Component*> components;

    virtual void EntityUpdate(double deltaTime) = 0;
    virtual void EntityRender() = 0;
};

#endif //SENGINE_ENTITY_H
