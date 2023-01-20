#pragma once
#include "Ayanami.hpp"

#include "Camera.hpp"
#include "Image.hpp"
#include "Ray.hpp"

class Frame {
public:
    Frame() {}
    Frame(int width, int height) : width(width), height(height) {
        data = new uint8_t[width * height * 3];
    }

    ~Frame() {
        delete[] data;
    }

    void render(Camera& camera);

public:
    uint8_t* data;
    int width, height;
};