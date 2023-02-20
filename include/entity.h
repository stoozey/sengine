#ifndef SENGINE_ENTITY_H
#define SENGINE_ENTITY_H

#include <vector>

#include "datatypes/vector3.h"
#include "components/component.h"

class Entity {
public:
    Entity();

    Vector3 position;

    virtual void PreUpdate(double deltaTime);
    virtual void Update(double deltaTime);
    virtual void PostUpdate(double deltaTime);

    virtual void PreRender();
    virtual void Render();
    virtual void PostRender();
};

#endif //SENGINE_ENTITY_H
