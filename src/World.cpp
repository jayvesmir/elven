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

World r_scene() {
    World world;

    shared_ptr<Material> ground_material = make_shared<Diffuse>(glm::vec3(0.5, 0.5, 0.5));
    world.append(make_shared<Sphere>(glm::vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = r_double();
            glm::vec3 center(a + 0.9 * r_double(), 0.2, b + 0.9 * r_double());

            if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    glm::vec3 albedo = r_vec3() * r_vec3();
                    sphere_material = make_shared<Diffuse>(albedo);
                    world.append(make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    glm::vec3 albedo = r_vec3(0.5, 1.0);
                    double fuzz = r_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.append(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    return world;
}