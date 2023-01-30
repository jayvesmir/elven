#pragma once

#include "Frame.hpp"
#include "World.hpp"
#include "Camera.hpp"

typedef struct Scene {
    Frame& frame;
    World& world;
    Camera& camera;

    void render();
} Scene;