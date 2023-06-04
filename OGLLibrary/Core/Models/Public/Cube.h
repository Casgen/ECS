#pragma once
#include "Model3D.h"
#include "VertexPos.h"

class Cube : public Model3D<VertexPos>
{
    
public:
    Cube()
    {
        vertices = {
            VertexPos(glm::vec4(-1.f, -1.f, 1.f,1.f)),  // A
            VertexPos(glm::vec4(1.f, -1.f, 1.f,1.f)),   // B
            VertexPos(glm::vec4(1.f, 1.f, 1.f,1.f)),    // C
            VertexPos(glm::vec4(-1.f, 1.f, 1.f,1.f)),   // D
            
            VertexPos(glm::vec4(-1.f, -1.f, -1.f,1.f)), // E
            VertexPos(glm::vec4(1.f, -1.f, -1.f,1.f)),  // F
            VertexPos(glm::vec4(1.f, 1.f, -1.f,1.f)),   // G
            VertexPos(glm::vec4(-1.f, 1.f, -1.f,1.f))   // H
        };

        indices = std::vector<unsigned int>{
            3,7,
            2,6,
            UINT_MAX,
            
            0,4,
            1,5,
            UINT_MAX,

            4,7,
            0,3,
            1,2,
            5,6,
            4,7,
            UINT_MAX
        };

        CreateIndexBuffer();
        CreateVertexBuffer();
    }
};
