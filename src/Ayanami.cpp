// STL
#include "Ayanami.hpp"

#include "Image.hpp"

int main(int argc, char** argv) {
    // Initial frame parameters
    int image_width = 256;
    int image_height = 256;

    // Render

    uint8_t* data = new uint8_t[image_width * image_height * 3];
    int i = 0;
    for (int y = image_height-1; y >= 0; y--) {
        for (int x = 0; x < image_width; x++) {
            auto r = double(x) / (image_width-1);
            auto g = double(y) / (image_height-1);
            auto b = 0.25;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            data[i] = ir;
            data[i + 1] = ig;
            data[i + 2] = ib;
            i += 3;
        }
    }

    if (!Image::save_ppm("image.ppm", image_width, image_height, data))
        printf("[Error] failed to save image");
        exit(-1);
    
    delete[] data;
}