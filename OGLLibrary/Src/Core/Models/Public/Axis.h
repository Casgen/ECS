#pragma once
#include "VertexLine.h"
#include "Model3D.h"


class Axis : public Model3D<VertexLine>
{
public:

    Axis()
    {

        //For X axis
        vertices.push_back({glm::vec4(0.0f,0.f,0.f,1.f), glm::vec4(1.0f,0.f,0.f,1.0f)});
        vertices.push_back({glm::vec4(1.0f,0.f,0.f,1.f), glm::vec4(1.0f,0.f,0.f,1.0f)});

        //For Y Axis
        vertices.push_back({glm::vec4(0.0f,0.f,0.f,1.f), glm::vec4(0.0f,1.f,0.f,1.0f)});
        vertices.push_back({glm::vec4(0.0f,1.f,0.f,1.f), glm::vec4(0.0f,1.f,0.f,1.0f)});

        //for Z Axis
        vertices.push_back({glm::vec4(0.0f,0.f,0.f,1.f), glm::vec4(0.0f,0.f,1.f,1.0f)});
        vertices.push_back({glm::vec4(0.0f,0.f,1.f,1.f), glm::vec4(0.0f,0.f,1.f,1.0f)});

        indices = {0,1,2,3,4,5};

        CreateVertexBuffer();
        CreateIndexBuffer();
    }

    void Translate(const glm::vec3& vec) override {}
};
