#include "Serializer.hpp"

namespace Serializer {
    SceneSerializer::SceneSerializer(const char* filename) {
        load_scene(filename);
    }

    void SceneSerializer::load_scene(const char* filename) {
        const char* src = file_content(filename);
        SceneSpec scene_spec;
        parse(src, &scene_spec);
        scene_spec.dump();
    }
}