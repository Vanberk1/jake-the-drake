#pragma once

#include "entity.h"
#include "system.h"
#include <unordered_map>
#include <map>

class EntityManager {
private:
    std::unordered_map<SystemType, System*> m_Systems;
    std::map<EntityId, Entity> m_Entities;
    int m_NextId; 

public:
    EntityManager();
    Entity CreateEntity()
    void DeleteEntity(Entity entity);
};