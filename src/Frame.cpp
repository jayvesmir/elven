#include "Frame.hpp"
#include <vector>
#include <execution>

#include "Timer.hpp"

void Frame::render(Camera& cam, const World& world) {
    Timer timer("Render");
    // Prepare row indices (I've no idea how to do this correctly)
    std::vector<int> rows;
    rows.reserve(height);
    for (int _y = 0; _y < height; _y++)
        rows.push_back(_y);

#define MT 1
#if MT

    std::for_each(std::execution::par, rows.begin(), rows.end(),
    [this, cam, world](int y) {
        for (int x = 0; x < width; x++) {
            auto u = glm::vec3(double(x) / (width-1));
            auto v = glm::vec3(double(y) / (height-1));

            Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            glm::vec3 color_vec = Renderer::per_pixel(ray, world);
            uint32_t color = Renderer::as_pixel(color_vec);

            data[x + y * width] = color;
        }
    });

#else

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

#endif
}