#include "Renderer.hpp"

namespace Renderer {

    bool hit_sphere(const glm::vec3& center, double radius, Ray& ray) {
        glm::vec3 oc = ray.origin - center;
        double a = glm::dot(ray.direction, ray.direction);
        double b = 2.0 * glm::dot(oc, ray.direction);
        double c = glm::dot(oc, oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        return (discriminant > 0);
    }
}