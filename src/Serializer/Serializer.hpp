#pragma once

#include <cstdio>
#include <string>

#include "Spec.hpp"
#include "FileIO.hpp"
#include "Parser.hpp"

namespace Serializer {
    class SceneSerializer {
    public:
        SceneSerializer(const char* filename);

        void load_scene(const char* filename);

    private:
    };
}