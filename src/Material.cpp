#include "Material.hpp"

bool Diffuse::scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const {
    glm::vec3 scatter_direction = (hit.normal - glm::normalize(r_sphere_vec3()));
    if (near_zero(scatter_direction))
        scatter_direction = hit.normal;
    
    ray_out = Ray(hit.point, scatter_direction);
    color = albedo;
    return true;
}

bool Metal::scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const {
    glm::vec3 reflected = glm::reflect(glm::normalize(ray.direction), hit.normal);
    ray_out = Ray(hit.point, glm::vec3(reflected + glm::vec3(blur) * glm::normalize(r_sphere_vec3())));
    color = albedo;
    return (glm::dot(ray_out.direction, hit.normal) < 0);
}

bool Dielectric::scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const {
    color = glm::vec3(1);
    float refraction_ratio = hit.front ? (1 / refraction_index) : refraction_index;

    glm::vec3 unit_direction = glm::normalize(ray.direction);
    glm::vec3 refracted = glm::refract(unit_direction, hit.normal, refraction_ratio);

    ray_out = Ray(hit.point, refracted);
    return DBL_TRUE_MIN;
}