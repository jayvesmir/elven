#pragma once
#include "Object.hpp"
#include "Utils.hpp"
#include "Material.hpp"

class World : public Object {
public:
    World() {}
    World(shared_ptr<Object> object) { append(object); }
    void clear() { objects.clear(); }
    void append(shared_ptr<Object> object) { objects.push_back(object); }
    virtual bool hit(Ray& ray, double t_min, double t_max, Hit& hit) const override;
public:
    std::vector<shared_ptr<Object>> objects;
};

World r_scene();