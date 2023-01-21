#include "Renderer.hpp"

namespace Renderer {
    uint32_t as_pixel(uint8_t r, uint8_t g, uint8_t b, double scale, int spp) {
        r = sqrt(scale * r);
        g = sqrt(scale * g);
        b = sqrt(scale * b);
        r *= 255;
		g *= 255;
		b *= 255;
        return (NULL << 24) | (b << 16) | (g << 8) | r;
    }

    uint32_t as_pixel(glm::vec3& color, double scale, int spp) {
        color.r = sqrt(scale * color.r);
        color.g = sqrt(scale * color.g);
        color.b = sqrt(scale * color.b);

        uint8_t r = (uint8_t)(clamp(color.r, 0.0, 0.999) * 256.0f);
		uint8_t g = (uint8_t)(clamp(color.g, 0.0, 0.999) * 256.0f);
		uint8_t b = (uint8_t)(clamp(color.b, 0.0, 0.999) * 256.0f);
		return (NULL << 24) | (b << 16) | (g << 8) | r;
    }

    glm::vec3 per_pixel(Ray& ray, const World& world, int depth) {
        if (depth <= 0)
            return glm::vec3(0);

        Hit hit;
        if (world.hit(ray, 0.0001, infinity, hit)) {
            glm::vec3 target = glm::vec3(hit.point) + glm::vec3(hit.normal) + r_sphere_vec3();
            Ray ray = Ray(hit.point, target - hit.point);
            return glm::vec3(0.5) * per_pixel(ray, world, depth - 1);
        }

        glm::vec3 dir = glm::normalize(ray.direction);
        double t = 0.5 * (dir.y + 1.0);
        return glm::vec3(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + glm::vec3(t) * glm::vec3(0.5, 0.7, 1.0);
    }
}