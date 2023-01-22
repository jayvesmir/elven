#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>

using std::shared_ptr;
using std::make_shared;

#include "Ray.hpp"

class Material;

struct Hit {
    glm::vec3 point;
    glm::vec3 normal;
    shared_ptr<Material> material;
    double t;
    bool front;

    inline void set_face_normal(Ray& ray, glm::vec3& surface_normal) {
        front = glm::dot(ray.direction, surface_normal) < 0;
        normal = front ? surface_normal : -surface_normal;
    }
};

class Object {
public:
    virtual bool hit(Ray& ray, double t_min, double t_max, Hit& hit) const = 0;
};

class Sphere : public Object {
public:
    Sphere() {}
    Sphere(glm::vec3 position, double radius, shared_ptr<Material> material) : position(position), radius(radius), material(material) {}
    virtual bool hit(Ray& ray, double t_min, double t_max, Hit& hit) const override;
public:
    glm::vec3 position;
    double radius;
    shared_ptr<Material> material;
};