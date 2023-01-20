#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "World.hpp"

namespace Renderer {
    uint32_t as_pixel(uint8_t r, uint8_t g, uint8_t b);
    uint32_t as_pixel(glm::vec3& color);
    glm::vec3 per_pixel(Ray& ray, World& world);
}