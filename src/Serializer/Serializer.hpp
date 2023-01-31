#pragma once

#include <cstdio>
#include <string>

#include "Spec.hpp"
#include "FileIO.hpp"
#include "Parser.hpp"

#include "Scene.hpp"

namespace Serializer {
    class SceneSerializer {
    public:
        SceneSerializer() = default;
        SceneSerializer(const char* filename);

        bool load_scene(const char* filename);
        Scene* get_scene() { return &scene; }

    private:
        Scene scene;
    };
}