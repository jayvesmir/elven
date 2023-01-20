#pragma once
#include <limits>
const double infinity = std::numeric_limits<double>::infinity();

#include <glm/vec3.hpp>
#include <glm/ext/matrix_transform.hpp>

class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

    glm::vec3 at(double t) const {
        return origin + glm::vec3(t) * direction;
    }

public:
    glm::vec3 origin;
    glm::vec3 direction;
};