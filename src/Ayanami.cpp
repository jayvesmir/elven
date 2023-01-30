// STL
#include "Ayanami.hpp"

#include "Frame.hpp"
#include "Camera.hpp"
#include "World.hpp"


void dump_render_info(Frame& frame, Camera& camera) {
    printf("\033[1;31m[Render Info]\n");
    printf("\033[1;32m[Frame]\n");
    printf("\033[0;37mWidth: %dpx Height: %dpx\nAspect ratio: %f\n", frame.width, frame.height, (double)frame.width / frame.height);
    printf("\033[0;37mSPP: %d Recursion Depth: %d\n", frame.samples_per_pixel, frame.rec_depth);
    printf("\033[1;32m[Camera]\n");
    printf("\033[0;37mPosition: %.2f %.2f %.2f\n", camera.origin.x, camera.origin.y, camera.origin.z);
    printf("\033[0;37mAperture: %.2f Focus Distance %.2f\n", camera.aperture, camera.focus_distance);
    fflush(stdout);
}

#include "Serializer/Serializer.hpp"

int main(int argc, char** argv) {
    Serializer::SceneSerializer serializer("C:/dev/projects/elven/sample_scene.elv");
#if 0
    const char* filename = "image.png";
    if (argc >= 2)
        filename = argv[1];

    // Initial frame parameters
    const auto aspect_ratio = 21.0 / 9.0;
    const int image_width = 1920;
    const int image_height = (int)(image_width / aspect_ratio);
    const int num_samples = 1 << 9; // 512
    const int max_depth = 50;
    Frame frame(image_width, image_height, num_samples, max_depth);

    // World
    World world = r_scene();
    {
        shared_ptr<Material> big_sphere = make_shared<Metal>(glm::vec3(0.7, 0.6, 0.5), 0.0);
        world.append(make_shared<Sphere>(glm::vec3(0.5, 1.0, 3), 1.0, big_sphere));
    }
    {
        shared_ptr<Material> big_sphere = make_shared<Diffuse>(glm::vec3(1.0, 0.5, 0.5));
        world.append(make_shared<Sphere>(glm::vec3(4, 1.5, 0), 1.0, big_sphere));
    }

    // Camera
    /* RTIOW Copy */

    glm::vec3 lookfrom(13, 2, 3);
    glm::vec3 lookat(0, 0, 0);
    glm::vec3 vup(0, 1, 0);
    double focus_distance = 10.0;
    double aperture = 0.1;

    Camera cam(lookfrom, lookat, vup, 20.0, aspect_ratio, aperture, focus_distance);
    dump_render_info(frame, cam);
    frame.render(cam, world);

    printf("\033[1;33m[Save] Saving %s\n", filename);
    if (!Image::save(filename, image_width, image_height, frame.data_as_uint8())) {
        printf("\033[1;31m[Error] failed to save %s\n", filename);
        exit(-1);
    }
    printf("\033[1;32m[Save] Successfully saved %s\n", filename);
    printf("\033[0;37m");
#endif
}