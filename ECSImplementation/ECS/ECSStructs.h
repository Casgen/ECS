#pragma once

struct ComponentStore
{
    size_t typeCount;
    size_t cap;
    size_t size;
    std::vector<size_t> sizesVec;
    std::vector<size_t> offsetsVec;
    void* data;
};

struct EntityStore
{
    std::vector<uint32_t> maskArray;
    std::vector<uint32_t> flagArray;
    uint32_t count;
    uint32_t cap;
};

struct QueryResult
{
    std::vector<uint32_t> queriedEntities;
};