// STL
#include "Ayanami.hpp"

#include "Frame.hpp"
#include "Material.hpp"

int main(int argc, char** argv) {
    const char* filename = "image.png";
    if (argc >= 2)
        filename = argv[1];

    // Initial frame parameters
    const auto aspect_ratio = 21.0 / 9.0;
    const int image_width = 1920;
    const int image_height = (int)(image_width / aspect_ratio);
    const int num_samples = 1 << 7; // 128
    const int max_depth = 50;
    Frame frame(image_width, image_height, num_samples, max_depth);

    // World
    World world;
    shared_ptr<Material> material_ground = make_shared<Diffuse>(glm::vec3(0.8, 0.8, 0.0));
    shared_ptr<Material> material_center = make_shared<Diffuse>(glm::vec3(1.0, 0.5, 0.5));
    shared_ptr<Material> material_left   = make_shared<Metal>(glm::vec3(0.8, 0.8, 0.8), 0.1);
    shared_ptr<Material> material_right  = make_shared<Metal>(glm::vec3(0.8, 0.6, 0.2), 1.0);

    world.append(make_shared<Sphere>(glm::vec3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.append(make_shared<Sphere>(glm::vec3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.append(make_shared<Sphere>(glm::vec3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.append(make_shared<Sphere>(glm::vec3( 1.0,    0.0, -1.0),   0.5, material_right));

    // Camera
    /* RTIOW Copy */

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    glm::vec3 origin = glm::vec3(0);
    Camera cam(viewport_width, viewport_height, focal_length, origin);
    frame.render(cam, world);

    printf("[Save] Saving %s\n", filename);
    if (!Image::save(filename, image_width, image_height, frame.data_as_uint8())) {
        printf("[Error] failed to save %s\n", filename);
        exit(-1);
    }
    printf("[Save] Successfully saved %s\n", filename);
}