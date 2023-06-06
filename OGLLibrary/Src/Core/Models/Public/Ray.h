#pragma once
#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 m_Origin, m_Direction;

    Ray() = default;
    Ray(const glm::vec3& origin, const glm::vec3 direction) : m_Origin(origin), m_Direction(glm::normalize(direction)) {}

    [[nodiscard]] glm::vec3 At(const float& t) const { return m_Origin + t * m_Direction; }
};
