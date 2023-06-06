#include "../Public/Grid.h"

#include <climits>
#include <cstdlib>
#include <glad/glad.h>
#include <iostream>

Grid::Grid(const glm::vec2& p0, const glm::vec2& p1, unsigned int m, unsigned int n, unsigned int type)
    : m_PrimitiveType(type), m_P0(glm::vec3(p0.x, 0.f, p0.y)), m_P1(glm::vec3(p1.x, 0.f, p1.y))
{
    vertices = std::vector<Vertex3D>();
    vertices.resize(m * n);


    float posX_div = glm::abs(p1.x - p0.x) / (static_cast<float>(m - 1));
    float posY_div = glm::abs(p1.y - p0.y) / (static_cast<float>(n - 1));

    float texX_div = 1.f / (static_cast<float>(m - 1));
    float texY_div = 1.f / (static_cast<float>(n - 1));

    unsigned int vertexCount = 0;

    for (unsigned int i = 0; i < n; i++)
    {
        float pos_y = p0.y + posY_div * static_cast<float>(i);
        float tex_y = 0.0f + texY_div * static_cast<float>(i);

        for (unsigned int j = 0; j < m; j++)
        {
            float pos_x = p0.x + posX_div * static_cast<float>(j);
            float tex_x = 0.0f + texX_div * static_cast<float>(j);

            Vertex3D vert = Vertex3D(glm::vec4(pos_x, 0.f, pos_y, 1.0f),
                                     glm::vec2(tex_x, tex_y),
                                     glm::vec4(tex_x, tex_y, 0.f, 1.0f),
                                     glm::vec3(0.f, 1.f, 0.f));
            vertices[vertexCount++] = vert;
        }
    }

    m_Normal = glm::vec3(0.f, 1.f, 0.f);
    m_CenterPoint = glm::vec3((p0.x + p1.x) / 2.f, 0.f, (p0.y + p1.y) / 2.f);

    switch (type)
    {
    case GL_TRIANGLES: FillIndicesTriangles(m, n);
        break;
    case GL_TRIANGLE_STRIP: FillIndicesTriangleStrip(m, n);
        break;
    case GL_PATCHES: FillIndicesQuads(m, n);
        break;
    }

    CreateVertexBuffer();
    CreateIndexBuffer();
}

void Grid::FillIndicesTriangleStrip(unsigned int& m, unsigned int& n)
{
    indices.resize(2 * m * (n - 1) + n);

    unsigned int indexCount = 0;

    for (unsigned int i = 0; i < n - 1; i++)
    {
        for (unsigned int j = 0; j < m; j++)
        {
            indices[indexCount++] = m * i + j;
            indices[indexCount++] = m * (i + 1) + j;
        }
        indices[indexCount++] = UINT_MAX;
    }

    indices.shrink_to_fit();
}

void Grid::FillIndicesTriangles(unsigned int& m, unsigned int& n)
{
    indices.resize(6 * (m - 1) * (n - 1));
    unsigned int indicesCount = 0;

    for (unsigned int i = 0; i < m - 1; i++)
    {
        unsigned int first = (i * m);

        for (int j = 0; j < n - 1; j++)
        {
            int a = first + j;
            int b = first + j + n;
            int c = first + j + 1;
            int d = first + j + n + 1;

            indices[indicesCount++] = a;
            indices[indicesCount++] = b;
            indices[indicesCount++] = c;

            indices[indicesCount++] = b;
            indices[indicesCount++] = d;
            indices[indicesCount++] = c;
        }
    }
}

void Grid::FillIndicesQuads(const unsigned int& m, const unsigned int& n)
{
    indices.resize((m - 1) * (n - 1) * 4);

    unsigned int indicesCount = 0;
    for (unsigned int i = 0; i < n - 1; i++)
    {
        for (unsigned int j = 0; j < m - 1; j++)
        {
            indices[indicesCount++] = m * i + j;
            indices[indicesCount++] = m * (i + 1) + j;
            indices[indicesCount++] = m * (i + 1) + j + 1;
            indices[indicesCount++] = m * i + j + 1;
        }
    }

    indices.shrink_to_fit();
}

bool Grid::IntersectGrid(const Ray& ray, glm::vec3& resultPoint) const
{
    const double denom = glm::dot(m_Normal, ray.m_Direction);
    if (abs(denom) > 1e-6)
    {
        glm::vec3 sub = m_CenterPoint - ray.m_Origin;
        float t = glm::dot(sub, m_Normal) / denom;
        resultPoint = ray.At(t);

        //Test whether the point is inside the grid or not
        glm::vec3 gridVector = m_P1 - m_CenterPoint;
        float gridArea = abs(gridVector.x * gridVector.z);

        glm::vec3 resultPointVector = resultPoint - m_CenterPoint;
        float resultPointArea = abs(resultPointVector.x * resultPointVector.z);

        return (t >= 0) && (gridArea >= resultPointArea);
    }
    return false;
}
