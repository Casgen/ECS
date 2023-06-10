#include "ECS.h"
#include <stdarg.h>
#include <stdexcept>

#define INIT_CAP 8

ECS::ECS(uint32_t countOfComponents, ...)
{
    if (countOfComponents > 32)
        throw std::runtime_error("Couldn't initialize ECS. You have reached a limit the number of supported components!");
    
    std::vector<size_t> componentSizes(32);
    std::vector<size_t> offsetsVec(32);
    size_t overallSize = 0;
    
    va_list va;
    
    va_start(va, countOfComponents);
    for (uint32_t i = 0; i < countOfComponents; i++)
    {
        size_t size = va_arg(va, size_t);
        componentSizes[i] = size;
        offsetsVec[i] = overallSize;
        overallSize += size;
    }
    va_end(va);

    m_ComponentStore = ComponentStore();
    
    m_ComponentStore.size = overallSize;
    m_ComponentStore.data = malloc(INIT_CAP * overallSize);
    m_ComponentStore.cap = INIT_CAP;
    m_ComponentStore.offsetsVec = offsetsVec;
    m_ComponentStore.sizesVec = componentSizes;
    m_ComponentStore.typeCount = countOfComponents;

    m_EntityPool = EntityStore();
    m_EntityPool.cap = INIT_CAP;
    m_EntityPool.count = 0;
    m_EntityPool.cap = INIT_CAP;
    m_EntityPool.maskArray = std::vector<uint32_t>(INIT_CAP);
    m_EntityPool.flagArray = std::vector<uint32_t>(INIT_CAP);
}


Entity ECS::CreateEntity()
{
    uint32_t newId;
    
    if (!deadIdQueue.empty())
    {
        newId = deadIdQueue.back();
        deadIdQueue.pop_back();
        m_EntityPool.flagArray[newId] = ENTITY_FLAG_IS_ALIVE;
        m_EntityPool.maskArray[newId] = 0;
    } else
    {
        // It's very important that the lastId gets incremented BEFORE the evaluation!
        // otherwise it will go out of bounds!
        newId = ++lastId;

        if (m_ComponentStore.cap == newId)
        {
            const size_t newDataSize = m_ComponentStore.size * m_ComponentStore.cap + m_ComponentStore.size * m_ComponentStore.cap / 2;
            m_ComponentStore.data = realloc(m_ComponentStore.data, newDataSize);
            m_ComponentStore.cap += m_ComponentStore.cap / 2;
        }

        m_EntityPool.flagArray[newId] = ENTITY_FLAG_IS_ALIVE;
        m_EntityPool.maskArray[newId] = 0;

    }

    return Entity(newId);
}


void ECS::RemoveComponent(uint32_t entityId, uint32_t componentId)
{
     static_cast<bool>(m_EntityPool.maskArray[entityId] & ~(1 << componentId));  
}

bool ECS::HasComponent(uint32_t entityId, uint32_t componentId)
{
    return static_cast<bool>(m_EntityPool.maskArray[entityId] & 1 << componentId);
}

void ECS::KillEntity(uint32_t entityId)
{
    m_EntityPool.flagArray[entityId] &= ~ENTITY_FLAG_IS_ALIVE;
}

QueryResult* ECS::Query(uint32_t countOfComponent, ...)
{
    va_list argList;

    uint32_t desiredMask = 0;

    va_start(argList, countOfComponent);
    for (int i = 0; i < countOfComponent; i++)
    {
        desiredMask |= 1 << va_arg(argList, uint32_t);
    }

    for (int i = 0; i < m_EntityPool.maskArray.size(); i++)
    {
        bool isAlive = m_EntityPool.flagArray[i] & ENTITY_FLAG_IS_ALIVE;
        bool hasDesiredComponents = desiredMask == (m_EntityPool.maskArray[i] & desiredMask);

        if ( isAlive && hasDesiredComponents)
        {
            m_QueryResult.queriedEntities.emplace_back(i);
        }
    }

    return &m_QueryResult;
}

uint32_t ECS::GetLastId() const
{
    return lastId;
}
