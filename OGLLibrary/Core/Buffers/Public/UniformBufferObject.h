#pragma once
#include <glew.h>
#include <unordered_map>

struct UniformBufferVariable
{
    unsigned int offset, size;
};

class UniformBufferObject
{
    unsigned int rendererId, size, offset = 0;

    std::unordered_map<std::string, UniformBufferVariable> uniformMap;

public:
    UniformBufferObject(const unsigned int& _size);
    ~UniformBufferObject();

    void Bind() const;
    void BindBase(const unsigned int& index) const;
    void BindRange(const unsigned int& index, const unsigned int& size, const unsigned int& offset) const;
    void Unbind() const;

    template<typename T>
    void addAndSetUniform(const std::string& name, const void* value)
    {
        UniformBufferVariable uniformParams = {offset, sizeof(T)};
        glBufferSubData(GL_UNIFORM_BUFFER,uniformParams.offset,uniformParams.size, value);
        uniformMap.emplace(name,uniformParams);
        offset += sizeof(T);
    }
    
    void setUniform(const std::string& name, const void* value) const;
};
