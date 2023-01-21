#include "Image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

namespace Image {
    ImageType get_image_type(const char* filename) {
        std::string ext = std::string(filename).erase(0, strcspn(filename, "."));

        if      (strcmp(ext.c_str(), ".png") == 0) return PNG;
        else if (strcmp(ext.c_str(), ".jpg") == 0 || strcmp(ext.c_str(), ".jpeg") == 0) return JPG;
        else if (strcmp(ext.c_str(), ".tga") == 0) return TGA;
        else if (strcmp(ext.c_str(), ".ppm") == 0) return PPM;
        return NONE;
    }

    bool save_ppm(const char* filename, int width, int height, uint8_t* data) {
        FILE* file = fopen(filename, "wb");
        if (!file)
            return false;

        fprintf(file, "P3\n%d %d\n255\n", width, height);
        
        int pixel_index = 0;
        for (int j = height - 1; j >= 0; j--) {
            for (int i = 0; i < width; i++) {
                fprintf(file, "%d %d %d\n", data[pixel_index], data[pixel_index + 1], data[pixel_index + 2]);
                pixel_index += 3;
            }
        }
        
        fclose(file);
        delete[] data;
        return true;
    }

    bool save_jpg(const char* filename, int width, int height, uint8_t* data, int quality) {
        stbi_flip_vertically_on_write(1);
        if (stbi_write_jpg(filename, width, height, 3, data, quality) < 0) {
            return false;
        } return true;
    }

    bool save_png(const char* filename, int width, int height, uint8_t* data, int stride) {
        stbi_flip_vertically_on_write(1);
        if (stbi_write_png(filename, width, height, 3, data, stride) < 0) {
            return false;
        }  return true;
    }

    bool save_tga(const char* filename, int width, int height, uint8_t* data) {
        stbi_flip_vertically_on_write(1);
        if (stbi_write_tga(filename, width, height, 3, data) < 0) {
            return false;
        }  return true;
    }

    bool save(const char* filename, int width, int height, uint8_t* data) {
        ImageType type = get_image_type(filename);
        if (filename) {
            switch (type) {
                case PNG:
                    return save_png(filename, width, height, data);
                    break;
                case JPG:
                    return save_jpg(filename, width, height, data);
                    break;
                case TGA:
                    return save_tga(filename, width, height, data);
                    break;
                case PPM:
                    return save_ppm(filename, width, height, data);
                    break;
                default:
                    return false;
            }
        }
        return false;
    }
}