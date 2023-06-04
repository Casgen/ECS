#pragma once
#include <glm.hpp>

struct TransformParams
{
   glm::vec3 translation = glm::vec3(0.f);
   float angleX, angleY, scale = 1.f;
};
