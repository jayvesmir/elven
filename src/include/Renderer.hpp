#pragma once
#include <glm/vec3.hpp>

#include "Ray.hpp"

namespace Renderer {

    double hit_sphere(const glm::vec3& center, double radius, Ray& ray);
}