#pragma once
#include "Model3D.h"

class Sphere : public Model3D<Vertex3D>
{
    glm::vec3 centerPosition = glm::vec3(0.f);
    glm::vec4 color = glm::vec4(1.f);

    float radius = 0.5;

public:

    Sphere() = default;

    /**
     * Constructs a Sphere
     * @param x_center - X-Coord of sphere's center position
     * @param y_center - Y-Coord of sphere's center position
     * @param z_center - Z-Coord of sphere's center position
     * @param col - Color of the sphere
     * @param r - Radius of the sphere
     * @param m - number of vertices in a column
     * @param n - Number of vertices in a row
     */
    
    Sphere(const float& x_center, const float& y_center, const float& z_center, const glm::vec4& col,
           const float r, const unsigned int& m = 10, const unsigned int& n = 10)
        : centerPosition(glm::vec4(x_center, y_center, z_center, 1.0f)), color(col), radius(r)
    {
        float phiUnit = glm::pi<float>() / (float)(m - 1);
        float thetaUnit = glm::pi<float>() * 2 / (float)(n - 1);

        float texX_div = 1.f / (static_cast<float>(m - 1));
        float texY_div = 1.f / (static_cast<float>(n - 1));

        for (unsigned int i = 0; i < m; i++)
        {
            float phi = phiUnit * (float)i;
            float tex_y = 0.0f + texY_div * static_cast<float>(i);

            for (unsigned int j = 0; j < n; j++)
            {
                float theta = thetaUnit * (float)j;
                float tex_x = 0.0f + texX_div * static_cast<float>(j);

                glm::vec3 vertexPosition = glm::vec3(
                    radius * glm::sin(phi) * glm::cos(theta) + centerPosition.x,
                    radius * glm::sin(phi) * glm::sin(theta) + centerPosition.y,
                    radius * glm::cos(phi) + centerPosition.z
                );

                glm::vec3 normal = glm::normalize(vertexPosition - glm::vec3(centerPosition));

                Vertex3D vertex = Vertex3D(
                    glm::vec4(vertexPosition, 1.0f),
                    glm::vec2(tex_x, tex_y),
                    color,
                    normal);

                vertices.push_back(vertex);
            }
        }


        for (unsigned int i = 0; i < m - 1; i++)
        {
            for (unsigned int j = 0; j < n; j++)
            {
                unsigned int first = i + j + ((n - 1) * i);
                indices.push_back(first);
                indices.push_back(first + n);
            }
            indices.push_back(UINT_MAX);
        }

        CreateVertexBuffer();
        CreateIndexBuffer();
    }

    void Translate(const glm::vec3& vec) override
    {
        modelMat = glm::translate(glm::identity<glm::mat4>(),vec - centerPosition);
    };

    [[nodiscard]] glm::vec3 GetCenterPosition() const { return centerPosition; }

    [[nodiscard]] glm::vec4 GetColor() const { return color; }

    [[nodiscard]] float GetRadius() const { return radius; }
};
