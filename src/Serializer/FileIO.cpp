#include "FileIO.hpp"

size_t file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

size_t file_size(const char* filename) {
    FILE* file = fopen(filename, "r");
    size_t size = file_size(file);
    fclose(file);
    return size;
}

const char* file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error while opening %s\n", filename);
        return NULL;
    }

    size_t size = file_size(file);
    if (size == 0) {
        return NULL;
    }

    char* contents = (char*)calloc(size, 1);
    size_t read_bytes = fread_s(contents, size, 1, size, file);
    fclose(file);
    return contents;
}