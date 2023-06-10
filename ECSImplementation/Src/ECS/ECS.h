#pragma once

#include <cstdint>
#include <vector>
#include "ECSStructs.h"
#include "Entity.h"
#include <cstring>


class ECS
{
    
public:

    ECS(uint32_t countOfComponent, ...);
    ECS();

    template<typename T>
    T* GetComponentCast(uint32_t entityId, uint32_t componentId)
    {
        // is it really working?
        return (T*) m_ComponentStore.data + entityId * m_ComponentStore.size + m_ComponentStore.offsetsVec[componentId];
    };

    void* GetComponent(uint32_t entityId, uint32_t componentId);

    Entity CreateEntity();

    template<typename T>
    void AddComponent(uint32_t entityId, uint32_t componentId, const T* data)
    {
        size_t size = m_ComponentStore.sizesVec[componentId];
        T* ptr = GetComponentCast<T>(entityId, componentId);
        memcpy(ptr, data, size);
        m_EntityPool.maskArray[entityId] |= 1 << componentId;
    };


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

    /**
    * Tells which ID was last inserted in ECS.
    */
    uint32_t lastId = -1;
    
};
