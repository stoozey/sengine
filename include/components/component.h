#ifndef SENGINE_COMPONENT_H
#define SENGINE_COMPONENT_H

class Component {
public:
    virtual void Update(double deltaTime) = 0;
    virtual void Render() = 0;
};

#endif //SENGINE_COMPONENT_H
