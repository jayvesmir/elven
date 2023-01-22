#include "Object.hpp"

/* RTIOW Copy */
bool Sphere::hit(Ray& ray, double t_min, double t_max, Hit& hit) const {
    glm::vec3 oc = ray.origin - position;
    auto a = glm::dot(ray.direction, ray.direction);
    auto half_b = glm::dot(oc, ray.direction);
    auto c = glm::dot(oc, oc) - radius * radius;

    auto discriminant = half_b * half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    hit.t = root;
    hit.point = ray.at(hit.t);
    hit.normal = (hit.point - position) / glm::vec3(radius);
    hit.material = material;

    return true;
}