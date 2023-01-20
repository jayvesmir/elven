#pragma once
#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

    glm::vec3 at(double t) const {
        return origin + glm::vec3(t) * direction;
    }

    glm::vec3 color();

public:
    glm::vec3 origin;
    glm::vec3 direction;
};

#if 0
glm::vec3 ray_color(const Ray& r) {
    glm::vec3 dir = glm::normalize(r.direction);
    auto t = 0.5 * (dir.y + 1.0);
    return glm::vec3(1.0 - t) * glm::vec3(1.0, 1.0, 1.0) + glm::vec3(t) * glm::vec3(1.0, 0.25, 0.25);
}
#endif