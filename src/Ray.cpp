#include "Ray.hpp"
#include "Renderer.hpp"

glm::vec3 Ray::color() {
    Ray r(*this);
    double t = Renderer::hit_sphere(glm::vec3(0, 0, -1), 0.5, r);
    if (t > 0) {
        glm::vec3 normal = glm::normalize(r.at(t) - glm::vec3(0, 0, -1));
        return glm::vec3(0.5) * (normal + glm::vec3(1));
    }

    glm::vec3 dir = glm::normalize(direction);
    t = 0.5 * (dir.y + 1.0);
    return glm::vec3(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + glm::vec3(t) * glm::vec3(0.5, 0.5, 1.0);
}