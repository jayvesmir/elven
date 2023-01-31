#include "Serializer.hpp"

namespace Serializer {
    SceneSerializer::SceneSerializer(const char* filename) {
        load_scene(filename);
    }

    bool SceneSerializer::load_scene(const char* filename) {
        const char* src = file_content(filename);
        SceneSpec scene_spec;

        if (!src)
            return false;
        if (!parse(src, &scene_spec))
            return false;
        scene_spec.dump();
        scene = Scene(scene_spec);
    }
}