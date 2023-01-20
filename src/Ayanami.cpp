// STL
#include "Ayanami.hpp"

#include "Frame.hpp"

int main(int argc, char** argv) {
    const char* filename = "image.png";
    if (argc >= 2)
        filename = argv[1];

    // Initial frame parameters
    const auto aspect_ratio = 21.0 / 9.0;
    const int image_width = 1920;
    const int image_height = (int)(image_width / aspect_ratio);
    const int num_samples = 25;
    Frame frame(image_width, image_height, num_samples);

    // World
    World world;
    world.append(make_shared<Sphere>(glm::vec3(0, 0, -1), 0.5));
    world.append(make_shared<Sphere>(glm::vec3(0,-100.5,-1), 100));

    // Camera
    /* RTIOW Copy */

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    glm::vec3 origin = glm::vec3(0);
    Camera cam(viewport_width, viewport_height, focal_length, origin);
    frame.render(cam, world);

    printf("[Save] Saving %s\n", filename);
    if (!Image::save_png(filename, image_width, image_height, frame.data_as_uint8())) {
        printf("[Error] failed to save image\n");
        exit(-1);
    }
    printf("[Save] Successfully saved %s\n", filename);
}