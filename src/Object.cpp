#include "Object.hpp"

bool Sphere::hit(Ray& ray, double t_min, double t_max, Hit& hit) const {
    // glm::vec3 oc = ray.origin - position;
    // double a = glm::dot(ray.direction, ray.direction);
    // double b = 2.0 * glm::dot(oc, ray.direction);
    // double c = glm::dot(oc, oc) - radius * radius;
    // double D = b * b - 4.0 * a * c;
    // if (D < 0) 
    //     return -1.0;
    
    // double discriminant_sqrt = glm::sqrt(D);
    // double root = (-b - discriminant_sqrt) / (2.0 * a);
    // if (root < t_min || root > t_max) {
    //     root = (-b + discriminant_sqrt) / (2.0 * a);
    //     if (root < t_min || root > t_max)
    //         return false;
    // }

    // hit.t = root;
    // hit.point = ray.at(root);
    // glm::vec3 surface_normal = (hit.point - position) / glm::vec3(radius);
    // hit.set_face_normal(ray, surface_normal);
    // return true;

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

    return true;
}