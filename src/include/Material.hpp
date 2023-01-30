#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include "Ray.hpp"
#include "Utils.hpp"
#include "Object.hpp"

enum MaterialType {
    DIFFUSE = 0,
    METAL,
    DIELECTRIC
};

class Material {
public:
    virtual bool scatter(const Ray& ray, const Hit& hit, glm::vec3& color, Ray& ray_out) const = 0;
};

class Diffuse : public Material {
public:
    Diffuse(const glm::vec3& albedo) : albedo(albedo) {}

    virtual bool scatter(
        const Ray& ray, const Hit& hit, glm::vec3& color, Ray& ray_out
    ) const override {
        glm::vec3 scatter_direction = hit.normal + glm::normalize(r_vec3());

        if (near_zero(scatter_direction))
            scatter_direction = hit.normal;

        ray_out = Ray(hit.point, scatter_direction);
        color = albedo;
        return true;
    }

public:
    glm::vec3 albedo;
};

class Metal : public Material {
public:
    Metal(const glm::vec3& albedo, double roughness) : albedo(albedo), roughness(roughness < 1 ? roughness : 1) {}

    virtual bool scatter(
        const Ray& ray, const Hit& hit, glm::vec3& color, Ray& ray_out
    ) const override {
        glm::vec3 reflected = glm::reflect(glm::normalize(ray.direction), hit.normal);
        ray_out = Ray(hit.point, reflected + glm::vec3(roughness) * r_sphere_vec3());
        color = albedo;
        return (glm::dot(ray_out.direction, hit.normal) > 0);
    }
public:
    glm::vec3 albedo;
    double roughness;
};

// Broken :O
// TODO: fix fr
class Dielectric : public Material {
public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {}
    virtual bool scatter(
        const Ray& ray, const Hit& hit, glm::vec3& color, Ray& ray_out
    ) const override {
        color = glm::vec3(1.0);
        double refraction_ratio = hit.front ? (1.0 / refraction_index) : refraction_index;

        glm::vec3 unit_direction = glm::normalize(ray.direction);
        double cos_theta = fmin(glm::dot(-unit_direction, hit.normal), 1.0);
        double sin_theta = glm::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        glm::vec3 direction;

        if (cannot_refract) {
            direction = glm::reflect(unit_direction, hit.normal);
        } else {
            direction = glm::refract(unit_direction, hit.normal, reinterpret_cast<float&>(refraction_ratio));
        }

        ray_out = Ray(hit.point, direction);
        return true;
    }
public:
    double refraction_index;
};