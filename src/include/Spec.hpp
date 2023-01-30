#pragma once
#include <glm/vec3.hpp>
#include <cstdio>
#include <vector>

#include "Material.hpp"
#include "Object.hpp"

typedef struct FrameSpec {
    int width;
    int height;
    int num_samples;
    int recursion_depth;

    void dump();
} FrameSpec;

typedef struct CameraSpec {
    glm::vec3 vup;
    glm::vec3 target;
    glm::vec3 position;
    double focus_distance;
    double aperture;

    void dump();
} CameraSpec;

typedef struct MaterialSpec {
    std::string name;
    glm::vec3 albedo;
    MaterialType type;
    double roughness;
    double refraction_index;

    void dump(int indent = 0);
    const char* type_as_string();
} MaterialSpec;

typedef struct ObjectSpec {
    ObjectType type;
    glm::vec3 position;
    double radius;
    MaterialSpec material;
    void resolve_material(std::vector<MaterialSpec>& materials);

    void dump();
    const char* type_as_string();
} ObjectSpec;

typedef struct SceneSpec {
    const char* filename;
    FrameSpec frame_spec;
    CameraSpec camera_spec;
    std::vector<MaterialSpec> materials;
    std::vector<ObjectSpec> objects;

    void dump();
    SceneSpec() {};
} SceneSpec;