#include "World.hpp"

bool World::hit(Ray& ray, double t_min, double t_max, Hit& hit) const {
    Hit tmp;
    bool b_hit = false;
    double closest = t_max;
    for (const shared_ptr<Object>& object : objects) {
        if (object->hit(ray, t_min, closest, tmp)) {
            b_hit = true;
            closest = tmp.t;
            hit = tmp;
        }
    }
    return b_hit;
}