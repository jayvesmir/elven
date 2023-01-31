#include "FileIO.hpp"

size_t file_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

size_t file_size(const char* filename) {
    FILE* file = fopen(filename, "r");
    size_t size = file_size(file);
    fclose(file);
    return size;
}

const char* file_content(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        printf("Error while opening %s\n", path);
        return NULL;
    }

    size_t size = file_size(file);
    if (size == 0) {
        return NULL;
    }

    char* contents = (char*)malloc(size + 1);
    size_t read_bytes = fread(contents, 1, size, file);
    fclose(file);

    // Make sure to null-terminate the file contents so that we don't get any string-related issues.
    contents[size] = '\0';
    return contents;
}