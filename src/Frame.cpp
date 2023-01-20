#include "Frame.hpp"
#include <algorithm>

void Frame::render(Camera& cam, World world) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            auto u = glm::vec3(double(x) / (width-1));
            auto v = glm::vec3(double(y) / (height-1));

            Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            glm::vec3 color_vec = Renderer::per_pixel(ray, world);
            uint32_t color = Renderer::as_pixel(color_vec);

            data[x + y * width] = color;
        }
    }
}