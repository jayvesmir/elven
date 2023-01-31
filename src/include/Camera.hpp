#pragma once
#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "Spec.hpp"
#include "Utils.hpp"

class Camera {
public:
    Camera() {}
    Camera(glm::vec3 position, glm::vec3 lookat, glm::vec3 vup, double fov, double aspect_ratio, double aperture, double focus_distance) : aperture(aperture), focus_distance(focus_distance) {
        double theta = deg2rad(fov);
        double h = glm::tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect_ratio * viewport_height;

        w = glm::normalize(position - lookat);
        u = glm::normalize(glm::cross(vup, w));
        v = glm::cross(w, u);

        origin = position;
        horizontal = glm::vec3(focus_distance) * glm::vec3(viewport_width) * u;
        vertical = glm::vec3(focus_distance) * glm::vec3(viewport_height) * v;
        lower_left_corner = origin - horizontal/glm::vec3(2) - vertical/glm::vec3(2) - glm::vec3(focus_distance) * w;
        lens_radius = aperture / 2;
    }

    Ray get_ray(glm::vec3 _u, glm::vec3 _v) const {
        glm::vec3 rd = glm::vec3(lens_radius) * r_disk_vec3();
        glm::vec3 offset = u * rd.x + v * rd.y;

        return Ray(origin + offset, lower_left_corner + _u * horizontal + _v * vertical - origin - offset);
    }

public:
    glm::vec3 origin, horizontal, vertical, lower_left_corner;
    glm::vec3 u, v, w;
    double lens_radius, aperture, focus_distance;
};