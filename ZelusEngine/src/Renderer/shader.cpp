#include "shader.h"

/**
 * Read in a shader file (.glsl) and create a c string of that shader file
 * @param filename - The name of the shader file to be read
 * @return - A pointer to the c string copy of the shader file.
 */
char* Shader::ReadShaderFiles(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.good()) {
        gLog->AddLog("[error] GLShader::ReadShaderFiles : Could not read shader: %s", filename.c_str());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    std::string temp = buffer.str();
    size_t size = temp.size() + 1;
    char* str = new char[size];

    for (unsigned int i = 0; i < size; i++) {
        str[i] = temp[i];
    }
    str[size - 1] = '\0';

    return str;
}