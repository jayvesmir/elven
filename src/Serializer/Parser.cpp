#include "Parser.hpp"

const char* whitespace = " \r\n";
const char* delimiters = " \r\n[],=\"";

inline const char* Token::content() {
    size_t length = end - beginning;
    char* content = (char*)malloc(length + 1);
    memcpy(content, beginning, length);
    content[length] = '\0';
    return (const char*)content;
}

Token::Token(char* src) {
    next = nullptr;
    beginning = src;
    end = src;
}

void append_token(Token** dest, Token src) {
    Token* temp = (Token*)calloc(1, sizeof(Token));;
    temp->beginning = src.beginning;
    temp->end = src.end;
    if (*dest) {
        Token* last_token = *dest;
        while(last_token->next) {
            last_token = last_token->next;
        }
        last_token->next = temp;
    } else { *dest = temp; }
}

bool lex(char* src, Token* token) {
    if (!src || !token) { 
        printf("\033[1;31m[Parser] Can't lex empty source");
        return false;
    }

    token->beginning = src;
    token->beginning += strspn(token->beginning, whitespace);
    token->end = token->beginning;
    if (*(token->end) == '\0') 
        return true;

    token->end += strcspn(token->beginning, delimiters);
    if (token->end == token->beginning) {
        token->end += 1;
    }
    return true;
}

bool parse(const char* src, SceneSpec* scene_spec) {
    Token* tokens = NULL;
    Token current_token((char*)src);
    size_t token_count = 0;

    while (lex(current_token.end, &current_token)) {
        if (current_token.end - current_token.beginning == 0) { break; }
        if (current_token == "," || current_token == "=")
            continue;
        append_token(&tokens, current_token);
        token_count++;
    }

    char* filename;
    FrameSpec frame_spec;
    CameraSpec camera_spec;
    std::vector<MaterialSpec> material_spec;
    std::vector<ObjectSpec> object_spec;

    while (tokens) {
        Token* current_token = tokens;
        if (*current_token == "frame") {
            Token* frame_tokens = tokens;
            while (frame_tokens) {
                if (*frame_tokens == "[")
                    break;

                if (*frame_tokens == "width"){
                    frame_spec.width = atoi(frame_tokens->next->content());
                    frame_tokens = frame_tokens->next->next;
                    continue;
                } else if (*frame_tokens == "height") {
                    frame_spec.height = atoi(frame_tokens->next->content());
                    frame_tokens = frame_tokens->next->next;
                    continue;
                } else if (*frame_tokens == "num_samples") {
                    frame_spec.num_samples = atoi(frame_tokens->next->content());
                    frame_tokens = frame_tokens->next->next;
                    continue;
                } else if (*frame_tokens == "recursion_depth") {
                    frame_spec.recursion_depth = atoi(frame_tokens->next->content());
                    frame_tokens = frame_tokens->next->next;
                    continue;
                } else if (*frame_tokens == "filename") {
                    const char* _filename = frame_tokens->next->content();
                    filename = (char*)calloc(strlen(_filename), sizeof(char));
                    memcpy(filename, _filename, strlen(_filename));
                    frame_tokens = frame_tokens->next->next;
                    continue;
                }
                frame_tokens = frame_tokens->next;
            }
        } else if (*current_token == "camera") {
            Token* camera_tokens = tokens;
            while (camera_tokens) {
                if (*camera_tokens == "[")
                    break;

                if (*camera_tokens == "position"){
                    float x, y, z;
                    sscanf(camera_tokens->next->content(), "%f", &x);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &y);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &z);
                    camera_spec.position = glm::vec3(x, y, z);
                    camera_tokens = camera_tokens->next->next;
                    continue;
                } else if (*camera_tokens == "target") {
                    float x, y, z;
                    sscanf(camera_tokens->next->content(), "%f", &x);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &y);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &z);
                    camera_spec.target = glm::vec3(x, y, z);
                    camera_tokens = camera_tokens->next->next;
                    continue;
                } else if (*camera_tokens == "vup") {
                    float x, y, z;
                    sscanf(camera_tokens->next->content(), "%f", &x);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &y);
                    camera_tokens = camera_tokens->next;
                    sscanf(camera_tokens->next->content(), "%f", &z);
                    camera_spec.vup = glm::vec3(x, y, z);
                    camera_tokens = camera_tokens->next->next;
                    continue;
                } else if (*camera_tokens == "focus_distance") {
                    double focus_distance;
                    sscanf(camera_tokens->next->content(), "%lf", &focus_distance);
                    camera_spec.focus_distance = focus_distance;
                    camera_tokens = camera_tokens->next->next;
                    continue;
                } else if (*camera_tokens == "aperture") {
                    double aperture;
                    sscanf(camera_tokens->next->content(), "%lf", &aperture);
                    camera_spec.aperture = aperture;
                    camera_tokens = camera_tokens->next->next;
                    continue;
                }
                camera_tokens = camera_tokens->next;
            }
        } else if (*current_token == "material") {
            Token* material_tokens = tokens;
            MaterialSpec material;
            while (material_tokens) {
                if (*material_tokens == "[")
                    break;

                if (*material_tokens == "name"){
                    std::string name("");
                    int quote_count = 0;
                    bool first = true;
                    bool second = false;
                    Token* name_tokens = material_tokens;
                    while (name_tokens) {
                        if (*name_tokens == "\"") {
                            if (quote_count > 0) {
                                break;
                            }
                            quote_count++;
                            name_tokens = name_tokens->next;
                            continue;
                        }

                        if (!first) {
                            std::string token(name_tokens->content());
                            token.insert(0, " ");
                            name.append(token.c_str());
                        } else if (second) {
                            name.append(name_tokens->content());
                            first = false;
                            second = false;
                        } else {
                            second = true;
                        }

                        name_tokens = name_tokens->next;
                    }
                    material.name = name;
                    material_tokens = material_tokens->next->next;
                    continue;
                } else if (*material_tokens == "type") {
                    Token* material_type = material_tokens->next;
                    if (*material_type == "diffuse")
                        material.type = DIFFUSE;
                    else if (*material_type == "metal")
                        material.type = METAL;
                    else if (*material_type == "dielectric")
                        material.type = DIELECTRIC;
                    material_tokens = material_tokens->next->next;
                    continue;
                } else if (*material_tokens == "albedo") {
                    int r, g, b;
                    sscanf(material_tokens->next->content(), "%i", &r);
                    material_tokens = material_tokens->next;
                    sscanf(material_tokens->next->content(), "%i", &g);
                    material_tokens = material_tokens->next;
                    sscanf(material_tokens->next->content(), "%i", &b);
                    material.albedo = glm::vec3(r/255.0, g/255.0, b/255.0);
                    material_tokens = material_tokens->next->next;
                    continue;
                } else if (*material_tokens == "roughness") {
                    double roughness;
                    sscanf(material_tokens->next->content(), "%lf", &roughness);
                    material.roughness = roughness;
                    material_tokens = material_tokens->next->next;
                    continue;
                } else if (*material_tokens == "refraction_index") {
                    double refraction_index;
                    sscanf(material_tokens->next->content(), "%lf", &refraction_index);
                    material.refraction_index = refraction_index;
                    material_tokens = material_tokens->next->next;
                    continue;
                }
                material_tokens = material_tokens->next;
            }
            if (strcmp("", material.name.c_str()) != 0)
                material_spec.push_back(material);
        } else if (*current_token == "object") {
            Token* object_tokens = tokens;
            ObjectSpec object;
            while (object_tokens) {
                if (*object_tokens == "[")
                    break;

                if (*object_tokens == "position"){
                    float x, y, z;
                    sscanf(object_tokens->next->content(), "%f", &x);
                    object_tokens = object_tokens->next;
                    sscanf(object_tokens->next->content(), "%f", &y);
                    object_tokens = object_tokens->next;
                    sscanf(object_tokens->next->content(), "%f", &z);
                    object.position = glm::vec3(x, y, z);
                    object_tokens = object_tokens->next->next;
                    continue;
                } else if (*object_tokens == "type") {
                    Token* object_type = object_tokens->next;
                    if (*object_type == "sphere")
                        object.type = SPHERE;
                    object_tokens = object_tokens->next->next;
                    continue;
                } else if (*object_tokens == "radius") {
                    double radius;
                    sscanf(object_tokens->next->content(), "%lf", &radius);
                    object.radius = radius;
                    object_tokens = object_tokens->next->next;
                    continue;
                } else if (*object_tokens == "material") {
                    std::string mat_name("");
                    int quote_count = 0;
                    bool first = true;
                    bool second = false;
                    Token* name_tokens = object_tokens;
                    while (name_tokens) {
                        if (*name_tokens == "\"") {
                            if (quote_count > 0) {
                                break;
                            }
                            quote_count++;
                            name_tokens = name_tokens->next;
                            continue;
                        }

                        if (!first) {
                            std::string token(name_tokens->content());
                            token.insert(0, " ");
                            mat_name.append(token.c_str());
                        } else if (second) {
                            mat_name.append(name_tokens->content());
                            first = false;
                            second = false;
                        } else {
                            second = true;
                        }

                        name_tokens = name_tokens->next;
                    }
                    object.material.name = mat_name;
                    object_tokens = object_tokens->next->next;
                    continue;
                }
                object_tokens = object_tokens->next;
            }
            object_spec.push_back(object);
        }
        
        tokens = tokens->next;
    }

    for (int i = 0; i < object_spec.size(); i++) {
        object_spec[i].resolve_material(material_spec);
    }

    scene_spec->filename = filename;
    scene_spec->frame_spec = frame_spec;
    scene_spec->camera_spec = camera_spec;
    scene_spec->materials = material_spec;
    scene_spec->objects = object_spec;

    return true;
}