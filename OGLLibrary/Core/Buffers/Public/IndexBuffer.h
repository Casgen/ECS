#pragma once
#include <vector>

class IndexBuffer
{
    unsigned int m_rendererID = 0;
    unsigned int m_Count = 0;
public:
    
    IndexBuffer() = default;
    IndexBuffer(const unsigned int* data, unsigned int count);
    IndexBuffer(const std::vector<unsigned int>& array);
    
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    [[nodiscard]] unsigned int getCount() const { return m_Count; }
};
