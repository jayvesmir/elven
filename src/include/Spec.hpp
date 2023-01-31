#pragma once
#include <glm/vec3.hpp>
#include <cstdio>
#include <vector>
#include <cstring>

#include "Object.hpp"

enum MaterialType {
    DIFFUSE = 0,
    METAL,
    DIELECTRIC
};

typedef struct FrameSpec {
    int width;
    int height;
    int num_samples;
    int recursion_depth;

    void dump(int indent = 0);
} FrameSpec;

typedef struct CameraSpec {
    glm::vec3 vup;
    glm::vec3 target;
    glm::vec3 position;
    double fov;
    double aspect_ratio;
    double focus_distance;
    double aperture;

    void dump(int indent = 0);
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

    void dump(int indent = 0);
    const char* type_as_string();
} ObjectSpec;

typedef struct SceneSpec {
    const char* filename;
    FrameSpec frame_spec;
    CameraSpec camera_spec;
    std::vector<ObjectSpec> objects;

    void dump(int indent = 0);
    SceneSpec() {};
} SceneSpec;