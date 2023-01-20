#include "Frame.hpp"

void Frame::render(Camera& cam) {
    int i = 0;
    for (int y = height-1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            auto u = glm::vec3(double(x) / (width-1));
            auto v = glm::vec3(double(y) / (height-1));

            Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            glm::vec3 color = ray.color();

            data[i] = (int)(color.r * 255.999);
            data[i + 1] = (int)(color.g * 255.999);
            data[i + 2] = (int)(color.b * 255.999);
            i += 3;
        }
    }
}