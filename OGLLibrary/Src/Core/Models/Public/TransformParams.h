#pragma once

#include "glm/ext/vector_float3.hpp"

struct TransformParams
{
   glm::vec3 translation = glm::vec3(0.f);
   float angleX, angleY, scale = 1.f;
};
