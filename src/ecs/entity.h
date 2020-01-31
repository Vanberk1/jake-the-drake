#pragma once

#include "component.h"
#include <unordered_map>

class Entity {
private:
    unsigned int id;
    std::unordered_map<ComponentType, Component*> m_Components;

public:
    Entity();
    ~Entity();
    bool HasComponent(ComponentType type) const;
    EntityId GetId() const;
};