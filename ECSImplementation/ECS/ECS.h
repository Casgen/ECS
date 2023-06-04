#pragma once

#include <vector>
#include "ECSStructs.h"
#include "Entity.h"


class ECS
{
    
public:

    ECS(uint32_t countOfComponent, ...);
    ECS();

    void* GetComponent(uint32_t entityId, uint32_t componentId);

    Entity CreateEntity();

    void AddComponent(uint32_t entityId, uint32_t componentId, const void* data);
    void RemoveComponent(uint32_t entityId, uint32_t componentId);
    bool HasComponent(uint32_t entityId, uint32_t componentId);

    void KillEntity(uint32_t entityId);

    QueryResult* Query(uint32_t countOfComponent, ...);

    uint32_t GetLastId() const;
    
private:
    EntityStore m_EntityPool;
    ComponentStore m_ComponentStore;
    std::vector<uint32_t> deadIdQueue;
    QueryResult m_QueryResult;

    uint32_t lastId = 0;
    
};
