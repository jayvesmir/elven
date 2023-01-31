#include "Spec.hpp"

void CameraSpec::dump(int indent) {
    printf("%*s\033[1;31m[Camera Spec]\n", (int)fmax(0, indent-1), "");
    printf("\033[1;37m");
    printf("%*sPosition: %.2f %.2f %.2f\n", indent, "", position.x, position.y, position.z);
    printf("%*sTarget: %.2f %.2f %.2f\n", indent, "", target.x, target.y, target.z);
    printf("%*sVUP: %.2f %.2f %.2f\n", indent, "", vup.x, vup.y, vup.z);
    printf("%*sFocus Distance: %.2lf Aperture: %.2lf\n", indent, "", focus_distance, aperture);
}

void FrameSpec::dump(int indent) {
    printf("%*s\033[1;31m[Frame Spec]\n", (int)fmax(0, indent-1), "");
    printf("\033[1;37m");
    printf("%*sWidth: %d Height: %d\n", indent, "", width, height);
    printf("%*sSPP: %d Recursion Depth: %d\n", indent, "", num_samples, recursion_depth);
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
    printf("%*s\033[1;31m[Material Spec]\n", (int)fmax(0, indent-1), "");
    printf("\033[1;37m");
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

void ObjectSpec::dump(int indent) {
    printf("%*s\033[1;31m[Object Spec]\n", (int)fmax(0, indent-1), "");
    printf("\033[1;37m");
    printf("%*sType: %s\n", indent, "", type_as_string());
    printf("%*sPosition: %.2f %.2f %.2f\n", indent, "", position.x, position.y, position.z);
    printf("%*sRadius [Sphere]: %.2lf\n", indent, "", radius);
    material.dump(indent + 2);
}

void ObjectSpec::resolve_material(std::vector<MaterialSpec>& materials) {
    for (int i = 0; i < materials.size(); i++) {
        if (strcmp(material.name.c_str(), materials[i].name.c_str()) == 0) {
            material = materials[i];
            return;
        }
    }
}

void SceneSpec::dump(int indent) {
    printf("\033[1;31m[Scene Spec] -> \033[1;32m%s\n", filename);
    frame_spec.dump(indent + 2);
    camera_spec.dump(indent + 2);
    for (int i = 0; i < objects.size(); i++) {
        objects[i].dump(indent + 2);
    }
}