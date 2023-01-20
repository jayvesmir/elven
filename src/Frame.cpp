#include "Frame.hpp"
#include <vector>
#include <execution>

#include "Timer.hpp"

#define MT 1
#define AA 1

inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

void Frame::render(Camera& cam, const World& world) {
    // Prepare row indices (I've no idea how to do this correctly)
    std::vector<int> rows;
    rows.reserve(height);
    for (int _y = 0; _y < height; _y++)
        rows.push_back(_y);

    Timer timer("Render");

#if MT

    std::for_each(std::execution::par, rows.begin(), rows.end(),
    [this, cam, world](int y) {
        for (int x = 0; x < width; x++) {
            #if AA

            glm::vec3 final_color(0.0f);
            for (int i = 0; i < samples_per_pixel-1; i++) {
                auto u = glm::vec3(double(x + random_double()) / (width-1));
                auto v = glm::vec3(double(y + random_double()) / (height-1));

                Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
                glm::vec3 color_vec = Renderer::per_pixel(ray, world);
                double scale = 1.0 / samples_per_pixel;
                color_vec *= glm::vec3(scale);
                final_color += color_vec;
            }
            uint32_t color = Renderer::as_pixel(final_color);

            #else

            auto u = glm::vec3(double(x) / (width-1));
            auto v = glm::vec3(double(y) / (height-1));

            Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            glm::vec3 color_vec = Renderer::per_pixel(ray, world);
            uint32_t color = Renderer::as_pixel(color_vec);
            
            #endif

            data[x + y * width] = color;
        }
    });

#else

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            glm::vec3 final_color(0.0f);
            for (int i = 0; i < samples_per_pixel-1; i++) {
                auto u = glm::vec3(double(x + random_double()) / (width-1));
                auto v = glm::vec3(double(y + random_double()) / (height-1));

                Ray ray(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
                glm::vec3 color_vec = Renderer::per_pixel(ray, world);
                double scale = 1.0 / samples_per_pixel;
                color_vec *= glm::vec3(scale);
                final_color += color_vec;
            }
            uint32_t color = Renderer::as_pixel(final_color);

            data[x + y * width] = color;
        }
    }

#endif

}