// STL
#include "Ayanami.hpp"

#include "Frame.hpp"
#include "Image.hpp"
#include "Camera.hpp"

int main(int argc, char** argv) {
    // Initial frame parameters
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = (int)(image_width / aspect_ratio);
    Frame frame(image_width, image_height);

    // Camera
    /* RTIOW Copy */

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    glm::vec3 origin = glm::vec3(0);
    glm::vec3 horizontal = glm::vec3(viewport_width, 0, 0);
    glm::vec3 vertical = glm::vec3(0, viewport_height, 0);
    glm::vec3 lower_left_corner = origin - horizontal/glm::vec3(2) - vertical/glm::vec3(2) - glm::vec3(0, 0, focal_length);
    Camera cam(viewport_width, viewport_height, focal_length, origin);

    frame.render(cam);

    if (!Image::save_ppm("image.ppm", image_width, image_height, frame.data))
        printf("[Error] failed to save image");
        exit(-1);
}