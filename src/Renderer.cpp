#include "Renderer.hpp"

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

namespace Renderer {
    uint32_t as_pixel(uint8_t r, uint8_t g, uint8_t b) {
        r *= 255;
		g *= 255;
		b *= 255;
        return (NULL << 24) | (b << 16) | (g << 8) | r;
    }

    uint32_t as_pixel(glm::vec3& color) {
        uint8_t r = (uint8_t)(clamp(color.r, 0.0, 0.999) * 256.0f);
		uint8_t g = (uint8_t)(clamp(color.g, 0.0, 0.999) * 256.0f);
		uint8_t b = (uint8_t)(clamp(color.b, 0.0, 0.999) * 256.0f);
		return (NULL << 24) | (b << 16) | (g << 8) | r;
    }

    glm::vec3 per_pixel(Ray& ray, const World& world) {
        Hit hit;
        if (world.hit(ray, 0, infinity, hit)) {
            return glm::vec3(0.5) * (hit.normal + glm::vec3(1));
        }

        glm::vec3 dir = glm::normalize(ray.direction);
        double t = 0.5 * (dir.y + 1.0);
        return glm::vec3(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + glm::vec3(t) * glm::vec3(0.5, 0.7, 1.0);
    }
}