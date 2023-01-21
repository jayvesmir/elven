#pragma once
#include "Ayanami.hpp"
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

double r_double();
int r_int();
glm::vec3 r_vec3();
glm::vec3 r_sphere_vec3();
double r_double(double min, double max);
int r_int(double min, double max);
glm::vec3 r_vec3(double min, double max);

/* RTIOW */
double clamp(double x, double min, double max);