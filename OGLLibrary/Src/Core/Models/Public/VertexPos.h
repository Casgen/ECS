#pragma once
#include <glm/vec4.hpp>

#include "../../Buffers/Public/VertexBufferLayout.h"

struct VertexPos
{
    glm::vec4 position;
    
    VertexPos(const glm::vec4& pos) : position(pos) {}
    
    [[nodiscard]] glm::vec4 GetPosition() const { return position; }
    
private:
    inline static VertexBufferLayout* m_Layout = nullptr;
    
public:
    static VertexBufferLayout& GetVertexBufferLayout()
    {
        if (m_Layout == nullptr)
        {
            m_Layout = new VertexBufferLayout();
            m_Layout->push<float>(4);
        }
        return *m_Layout;
    }
};
