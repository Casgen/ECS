#pragma once
#include <cstdint>

struct Entity
{
    Entity(uint32_t id) : id(id) {}
    Entity() {}
    
    uint32_t id;
};

enum EntityMask
{
    ENTITY_FLAG_IS_ALIVE = 1,
};
