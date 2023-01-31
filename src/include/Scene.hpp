#pragma once

#include "Spec.hpp"
#include "Frame.hpp"
#include "World.hpp"
#include "Camera.hpp"

class Scene {
private:
    const char* filename;
    Frame frame;
    World world;
    Camera camera;

public:
    void render();
    bool save();
    Scene() = default;
    Scene(SceneSpec& spec);
};