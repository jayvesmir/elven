#include "Renderer.hpp"

namespace Renderer {

    double hit_sphere(const glm::vec3& center, double radius, Ray& ray) {
        glm::vec3 oc = ray.origin - center;
        double a = glm::dot(ray.direction, ray.direction);
        double b = 2.0 * glm::dot(oc, ray.direction);
        double c = glm::dot(oc, oc) - radius * radius;
        double D = b * b - 4 * a * c;
        if (D < 0) {
            return -1.0;
        } else {
            return (-b - glm::sqrt(D)) / (2.0 * a);
        }
    }
}