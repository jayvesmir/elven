// STL
#include "Ayanami.hpp"

#include "Scene.hpp"
#include "Serializer.hpp"

int main(int argc, char** argv) {
    Serializer::SceneSerializer serializer;
    if (!serializer.load_scene("sample_scene.elv"))
        exit(-1);
    Scene* scene = serializer.get_scene();
    scene->render();
    scene->save();
    scene->free();
}