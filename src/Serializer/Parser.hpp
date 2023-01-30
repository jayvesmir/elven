#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iterator>

#include "Spec.hpp"
#include "Frame.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Object.hpp"
#include "Material.hpp"

typedef struct Token {
    char* beginning;
    char* end;
    Token* next;
    Token(char* src);

    const char* content();
    inline bool operator==(const char* str) {
        return (strcmp(strlwr((char*)str), strlwr((char*)content())) == 0);
    }
} Token;

bool lex(const char* src, Token* token);
bool parse(const char* src, SceneSpec* scene_spec);

void append_token(Token** dest, Token src);