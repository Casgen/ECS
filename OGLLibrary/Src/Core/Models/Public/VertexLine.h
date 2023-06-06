#pragma once

#include "../../Buffers/Public/VertexBufferLayout.h"

#include <glm/vec4.hpp>


class VertexBufferLayout;

struct VertexLine
{
    glm::vec4 position;
    glm::vec4 color;

private:
    inline static VertexBufferLayout* m_Layout = nullptr;
    
public:
    static VertexBufferLayout& GetVertexBufferLayout()
    {
        if (m_Layout == nullptr)
        {
            m_Layout = new VertexBufferLayout();
            m_Layout->push<float>(4);
            m_Layout->push<float>(4);
        }
        return *m_Layout;
    }
};
