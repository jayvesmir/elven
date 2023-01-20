#pragma once
#include <glm/vec3.hpp>

#include "Ray.hpp"

class Camera {
public:
    Camera() {}
    Camera(double width, double height, double focal_length, glm::vec3 origin) 
        : viewport_width(width), viewport_height(height), focal_length(focal_length), origin(origin) {
        horizontal = glm::vec3(viewport_width, 0, 0);
        vertical = glm::vec3(0, viewport_height, 0);
        lower_left_corner = origin - horizontal/glm::vec3(2) - vertical/glm::vec3(2) - glm::vec3(0, 0, focal_length);
    }

public:
    double viewport_width, viewport_height, focal_length;
    glm::vec3 origin, horizontal, vertical, lower_left_corner;
};