#include "Utils.hpp"

double r_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static thread_local std::mt19937 generator;
    return distribution(generator);
}

double r_double(double min, double max) {
    return min + (max-min) * r_double();
}

int r_int() {
    return (int)r_double();
}

int r_int(double min, double max) {
    return min + (max-min) * r_int();
}

glm::vec3 r_vec3() {
    return glm::vec3(r_double(), r_double(), r_double());
}

glm::vec3 r_vec3(double min, double max) {
    return glm::vec3(r_double(min, max), r_double(min, max), r_double(min, max));
}

glm::vec3 r_sphere_vec3() {
    while (true) {
        glm::vec3 vec = r_vec3(-1,1);
        if (glm::dot(vec, vec) >= 1) continue;
        return vec;
    }
}

double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}