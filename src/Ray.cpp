#include "Ray.hpp"
#include "Renderer.hpp"

glm::vec3 Ray::color() {
    Ray r(*this);
    if (Renderer::hit_sphere(glm::vec3(0, 0, -1), 0.5, r))
        return glm::vec3(0.5, 1.0, 0.5);

    glm::vec3 dir = glm::normalize(direction);
    auto t = 0.5 * (dir.y + 1.0);
    return glm::vec3(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + glm::vec3(t) * glm::vec3(0.5, 0.7, 1.0);
}