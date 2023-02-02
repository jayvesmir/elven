#pragma once
#include <cstdio>
#include <cstdlib>

#include <string>
#include <iterator>
#include <ios>
#include <fstream>

size_t file_size(FILE* file);
size_t file_size(const char* filename);
const char* file_content(const char* filename);