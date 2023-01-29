#pragma once
#include <glm/vec3.hpp>
#include "Ray.hpp"

#define deg2rad(x) x*(3.141592/180.0)

class Camera {
public:
    Camera() {}
    Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 vup, double fov, double aspect_ratio) {
        double theta = deg2rad(fov);
        double h = glm::tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        glm::vec3 w = glm::normalize(position - lookat);
        glm::vec3 u = glm::normalize(glm::cross(vup, w));
        glm::vec3 v = glm::cross(w, u);

        origin = position;
        horizontal = glm::vec3(viewport_width) * u;
        vertical = glm::vec3(viewport_height) * v;
        lower_left_corner = origin - horizontal/glm::vec3(2) - vertical/glm::vec3(2) - w;
    }

    Ray get_ray(glm::vec3 u, glm::vec3 v) const {
        return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

public:
    glm::vec3 origin, horizontal, vertical, lower_left_corner;
};