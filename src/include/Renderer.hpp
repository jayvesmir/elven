#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "World.hpp"
#include "Utils.hpp"

namespace Renderer {
    uint32_t as_pixel(uint8_t r, uint8_t g, uint8_t b, double scale, int spp);
    uint32_t as_pixel(glm::vec3& color, double scale, int spp);
    glm::vec3 per_pixel(Ray& ray, const World& world, int depth);
}