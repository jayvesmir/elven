#include "Scene.hpp"

void Scene::render() {
    frame.render(camera, world);
}

bool Scene::save() {
    printf("\033[1;33m[Save] Saving %s\n", filename);
    if (!Image::save(filename, frame.width, frame.height, frame.data_as_uint8())) {
        printf("\033[1;31m[Error] failed to save %s\n", filename);
        exit(-1);
    }
    printf("\033[1;32m[Save] Successfully saved %s\n", filename);
    printf("\033[0;37m");
    
}

Scene::Scene(SceneSpec& spec) : filename(spec.filename) {
    frame = Frame(spec.frame_spec);
    camera = Camera(spec.camera_spec);
    for (ObjectSpec obj : spec.objects) {
        switch (obj.type) {
            case SPHERE:
                shared_ptr<Material> material;
                switch (obj.material.type) {
                    case DIFFUSE:
                        material = make_shared<Diffuse>(obj.material.albedo);
                        break;
                    case METAL:
                        material = make_shared<Metal>(obj.material.albedo, obj.material.roughness);
                        break;
                    case DIELECTRIC:
                        material = make_shared<Dielectric>(obj.material.refraction_index);
                        break;
                    default:
                        material = make_shared<Diffuse>(glm::vec3(0.0));
                        break;
                }
                world.append(make_shared<Sphere>(obj.position, obj.radius, material));
                break;
        }
    }
}