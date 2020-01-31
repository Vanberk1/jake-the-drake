#pragma once

#include "entity.h"

class System {
public:
    std::vector<Entity*> m_Entities;

    virtual ~System() = 0;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
};