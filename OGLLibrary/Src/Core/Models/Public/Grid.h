#pragma once
#include "Model3D.h"
#include "glad/glad.h"
#include "Ray.h"


class Grid : public Model3D<Vertex3D>
{
    unsigned int m_PrimitiveType;

    glm::vec3 m_Normal, m_CenterPoint;
    glm::vec3 m_P0, m_P1;
    
public:
    Grid() {};
    Grid(const glm::vec2& p0, const glm::vec2& p1, unsigned int m = 8, unsigned int n = 8, unsigned int type = GL_TRIANGLE_STRIP);

    void FillIndicesTriangleStrip(unsigned int& m, unsigned int& n);
    void FillIndicesTriangles(unsigned int& m, unsigned int& n);
    void FillIndicesQuads(const unsigned int& m, const unsigned int& n);

    [[nodiscard]] unsigned int GetPrimitiveType() const {return m_PrimitiveType;}

    bool IntersectGrid(const Ray& ray, glm::vec3&) const;
};
