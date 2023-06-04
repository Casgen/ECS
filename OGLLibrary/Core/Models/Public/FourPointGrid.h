#pragma once
#include <vec3.hpp>
#include <vec4.hpp>
#include <ext/matrix_transform.hpp>

#include "Model3D.h"
#include "Ray.h"

/*class FourPointGrid : Model3D<Vertex3D>
{
public:
    FourPointGrid(glm::vec3 location, const float& scale)
    {
        glm::vec4 m_P00(glm::vec4(-1.f,-1.f,0.f, 1.f));
        glm::vec4 m_P01(glm::vec4(-1.f,1.f,0.f, 1.f));
        glm::vec4 m_P10(glm::vec4(1.f,-1.f,0.f, 1.f));
        glm::vec4 m_P11(glm::vec4(1.f,1.f,0.f, 1.f));

        m_ScaleMat = glm::scale(glm::identity<glm::mat4>(),glm::vec3(1.f));
        m_TranslateMat = glm::translate(glm::identity<glm::mat4>(),location);
        m_RotateMat = glm::identity<glm::mat4>();

        m_ModelMat = m_TranslateMat * m_RotateMat * m_ScaleMat;

        m_Normal = glm::vec3(0.f, 0.f, 1.f);

        vertices[0] = Vertex3D(m_P00,glm::vec2(0.f), glm::vec4(0.f), m_Normal);
        vertices[1] = Vertex3D(m_P10,glm::vec2(1.f, 0.f), glm::vec4(1.f,0.f, 0.f, 0.f), m_Normal);
        vertices[2] = Vertex3D(m_P01,glm::vec2(0.f, 1.f), glm::vec4(0.f, 1.f , 0.f, 0.f), m_Normal);
        vertices[3] = Vertex3D(m_P11,glm::vec2(1.f,1.f), glm::vec4(1.f, 1.f, 0.f, 0.f), m_Normal);

        indices = {0,1,2,3};

        CreateVertexBuffer();
        CreateIndexBuffer();
    }
    
bool IntersectGrid(const Ray& ray, glm::vec3& resultPoint) const
{
    const double denom = glm::dot(m_Normal,ray.m_Direction);
    if (abs(denom) > 1e-6)
    {
        glm::vec3 sub = m_Location - ray.m_Origin;
        float t = glm::dot(sub, m_Normal) / denom;
        resultPoint = ray.At(t);

        //Test whether the point is inside the grid or not
        glm::vec3 gridVector = m_P1 - m_Location;
        float gridArea = abs(gridVector.x * gridVector.z);
        
        glm::vec3 resultPointVector = resultPoint - m_Location;
        float resultPointArea = abs(resultPointVector.x * resultPointVector.z);
        
        return (t >= 0) && (gridArea >= resultPointArea);
    }
    return false;
}
    
private:
    glm::vec3 m_Normal;
    glm::vec3 m_Location;

    glm::vec4 m_P00, m
    
};*/
