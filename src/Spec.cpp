#include "Spec.hpp"

void CameraSpec::dump() {
    printf("[Camera Spec]\n");
    printf("Position: %.2f %.2f %.2f\n", position.x, position.y, position.z);
    printf("Target: %.2f %.2f %.2f\n", target.x, target.y, target.z);
    printf("VUP: %.2f %.2f %.2f\n", vup.x, vup.y, vup.z);
    printf("Focus Distance: %.2lf Aperture: %.2lf\n", focus_distance, aperture);
}

void FrameSpec::dump() {
    printf("[Frame Spec]\n");
    printf("Width: %d Height: %d\n", width, height);
    printf("SPP: %d Recursion Depth: %d\n", num_samples, recursion_depth);
}

const char* MaterialSpec::type_as_string() {
    switch (type) {
        case DIFFUSE:
            return "Diffuse";
        case METAL:
            return "Metal";
        case DIELECTRIC:
            return "Dielectric";
    }
}

void MaterialSpec::dump(int indent) {
    printf("%*s[Material Spec]\n", indent, "");
    printf("%*sName: %s\n", indent, "", name.c_str());
    printf("%*sType: %s\n", indent, "", type_as_string());
    printf("%*sAlbedo [Diffuse, Metal]: %.2f %.2f %.2f\n", indent, "", albedo.r, albedo.g, albedo.b);
    printf("%*sRoughness [Metal]: %.2lf Refraction Index [Dielectric]: %.2lf\n", indent, "", roughness, refraction_index);
}

const char* ObjectSpec::type_as_string() {
    switch (type) {
        case SPHERE:
            return "Sphere";
    }
}

void ObjectSpec::dump() {
    printf("[Object Spec]\n");
    printf("Type: %s\n", type_as_string());
    printf("Position: %.2f %.2f %.2f\n", position.x, position.y, position.z);
    printf("Radius [Sphere]: %.2lf\n", radius);
    material.dump(2);
}

void ObjectSpec::resolve_material(std::vector<MaterialSpec>& materials) {
    for (int i = 0; i < materials.size(); i++) {
        if (strcmp(material.name.c_str(), materials[i].name.c_str()) == 0) {
            material = materials[i];
            return;
        }
    }
}

void SceneSpec::dump() {
    printf("[Scene Spec] -> %s\n", filename);
    frame_spec.dump();
    camera_spec.dump();
    for (int i = 0; i < materials.size(); i++) {
        materials[i].dump();
    }
    for (int i = 0; i < objects.size(); i++) {
        objects[i].dump();
    }
}