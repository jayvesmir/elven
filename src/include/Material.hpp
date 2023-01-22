#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include "Ray.hpp"
#include "Utils.hpp"
#include "Object.hpp"

class Material {
public:
    virtual bool scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const = 0;
};

class Diffuse : public Material {
public:
    Diffuse(glm::vec3 albedo) : albedo(albedo) {}

    virtual bool scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const override;
public:
    glm::vec3 albedo;
};

// Currently Broken
class Metal : public Material {
public:
    Metal(glm::vec3 albedo, double blur) : albedo(albedo), blur(blur) {}

    virtual bool scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const override;
public:
    glm::vec3 albedo;
    double blur;
};

class Dielectric : public Material {
public:
    Dielectric(double refraction_index) : refraction_index(refraction_index) {}

    virtual bool scatter(Ray& ray, Hit& hit, glm::vec3& color, Ray& ray_out) const override;
public:
    double refraction_index;
};