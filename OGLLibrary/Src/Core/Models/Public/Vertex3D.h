#pragma once

#include "../../Buffers/Public/VertexBufferLayout.h"
#include "glm/ext/vector_float4.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

struct Vertex3D
{
    glm::vec4 position;
    glm::vec2 texCoord;
    glm::vec4 color;
    glm::vec3 normal;
    

    Vertex3D(const glm::vec4& pos, const glm::vec2& tex, const glm::vec4& col, const glm::vec3& norm)
        : position(pos), texCoord(tex), color(col), normal(norm)
    {}

    Vertex3D() {}


    [[nodiscard]] glm::vec4 getPosition() const { return position; }
    [[nodiscard]] glm::vec2 getTexCoord() const { return texCoord; }


private:
    inline static VertexBufferLayout* m_Layout = nullptr;
    
public:
    static VertexBufferLayout& GetVertexBufferLayout()
    {
        if (m_Layout == nullptr)
        {
            m_Layout = new VertexBufferLayout();
            m_Layout->push<float>(4);
            m_Layout->push<float>(2);
            m_Layout->push<float>(4);
            m_Layout->push<float>(3);
        }
        return *m_Layout;
    }
};
