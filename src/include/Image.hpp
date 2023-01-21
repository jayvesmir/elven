#pragma once
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <string>

namespace Image {
    enum ImageType {
        PNG = 0,
        JPG,
        TGA,
        PPM,
        NONE
    };

    ImageType get_image_type(const char* filename);

    bool save_ppm(const char* filename, int width, int height, uint8_t* data);
    bool save_jpg(const char* filename, int width, int height, uint8_t* data, int quality = 95);
    bool save_png(const char* filename, int width, int height, uint8_t* data, int stride = 0);
    bool save_tga(const char* filename, int width, int height, uint8_t* data);
    bool save(const char* filename, int width, int height, uint8_t* data);
}