#include "shader.h"
/*!
 * Constructor for a shader with a vertex shader and a fragment shader
 * @param vertexShader - the filename for the vertex shader
 * @param fragmentShader - the filename for the fragment shader
 */

Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader) {
    vertexPath = vertexShader;
    fragmentPath = fragmentShader;

    char* vertexShaderString;
    char* fragmentShaderString;

    vertexShaderString = ReadShaderFiles(vertexShader);
    fragmentShaderString = ReadShaderFiles(fragmentShader);

    GLuint vertexHandle, fragmentHandle;

    vertexHandle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexHandle, 1, &vertexShaderString, NULL);
    glCompileShader(vertexHandle);

    char* str;
    GLint logLength;
    GLint success;

    glGetShaderiv(vertexHandle, GL_INFO_LOG_LENGTH, &logLength);
    glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &success);

    if (!success) {
        str = new char[logLength];
        glGetShaderInfoLog(vertexHandle, logLength, NULL, str);
        std::cout << str << std::endl;
        delete[] str;
    }

    fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentHandle, 1, &fragmentShaderString, NULL);
    glCompileShader(fragmentHandle);

    glGetShaderiv(fragmentHandle, GL_INFO_LOG_LENGTH, &logLength);
    glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &success);

    if (!success) {
        str = new char[logLength];
        glGetShaderInfoLog(fragmentHandle, logLength, NULL, str);
        std::cout << str << std::endl;
        delete[] str;
    }

    handle = glCreateProgram();
    glAttachShader(handle, vertexHandle);
    glAttachShader(handle, fragmentHandle);

    glLinkProgram(handle);

    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLength);
    glGetShaderiv(handle, GL_LINK_STATUS, &success);

    if (!success) {
        str = new char[logLength];
        glGetShaderInfoLog(handle, logLength, NULL, str);
        std::cout << str << std::endl;
        delete[] str;
    }

    glDeleteShader(vertexHandle);
    glDeleteShader(fragmentHandle);

    free(vertexShaderString);
    free(fragmentShaderString);

    gLog->AddLog("[info] Shaders Loaded: %s and %s", vertexPath.c_str(), fragmentPath.c_str());
}

/*!
 * Destructor of the shader object
 * @details - will remove all shader objects
 */
Shader::~Shader() {
    glDeleteShader(handle);
    gLog->AddLog("[info] Shaders Deleted: %s and %s", vertexPath.c_str(), fragmentPath.c_str());
}

/*!
 * Read in a shader file (.glsl) and create a c string of that shader file
 * @param filename - The name of the shader file to be read
 * @return - A pointer to the c string copy of the shader file.
 */
char* Shader::ReadShaderFiles(const std::string& filename) {

    std::ifstream file(filename); 

    if (!file.good()) {
        gLog->AddLog("[error] Shader::ReadShaderFiles : Could not read shader: %s", filename.c_str());
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

/*!
 * Use this objects shader program {glUseProgram(handle)}
 * @return void
 */
void Shader::Use() {
    glUseProgram(handle);
}

/*!
 * Stop using this objects shader program {glUseProgram(0)}
 * @return void
 */
void Shader::UnUse() {
    glUseProgram(0);
}

/*!
 * Create a uniform location and value for a boolean inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - Boolean value passed to the shader
 */
void Shader::SetBool(const std::string& name, bool value) const {
    glUseProgram(handle);
    glUniform1i(glGetUniformLocation(handle, name.c_str()), (int)value);
}

/*!
 * Create a uniform location and value for a integer inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - Integer value passed to the shader
 */
void Shader::SetInt(const std::string& name, int value) const {
    glUseProgram(handle);
    glUniform1i(glGetUniformLocation(handle, name.c_str()), value);
}

/*!
 * Create a uniform location and value for a float inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value
 */
void Shader::SetFloat(const std::string& name, float value) const {
    glUseProgram(handle);
    glUniform1f(glGetUniformLocation(handle, name.c_str()), value);
}

/*!
 * Create a uniform location and value for a 2D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 2D Vector value passed to the shader
 */
void Shader::SetVec2(const std::string& name, glm::vec2& value) const {
    glUseProgram(handle);
    glUniform2fv(glGetUniformLocation(handle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 2D Vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of X passed to the shader
 * @param y - Value of Y passed to the shader
 */
void Shader::SetVec2(const std::string& name, float x, float y) const {
    glUseProgram(handle);
    glUniform2f(glGetUniformLocation(handle, name.c_str()), x, y);
}

/*!
 * Create a uniform location and value for a 3D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 3D Vector value passed to the shader
 */
void Shader::SetVec3(const std::string& name, glm::vec3& value) const {
    glUseProgram(handle);
    glUniform3fv(glGetUniformLocation(handle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 3D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of x passed to the shader
 * @param y - Value of y passed to the shader
 * @param z - Value of z passed to the shader
 */
void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
    glUseProgram(handle);
    glUniform3f(glGetUniformLocation(handle, name.c_str()), x, y, z);
}

/*!
 * Create a uniform location and value for a 4D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 4D Vector value passed to the shader
 */
void Shader::SetVec4(const std::string& name, glm::vec4& value) const {
    glUseProgram(handle);
    glUniform4fv(glGetUniformLocation(handle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 4D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of x passed to the shader
 * @param y - Value of x passed to the shader
 * @param z - Value of x passed to the shader
 * @param w - Value of x passed to the shader
 */
void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    glUseProgram(handle);
    glUniform4f(glGetUniformLocation(handle, name.c_str()), x, y, z, w);
}

/*!
 * Create a uniform location and value for a 2D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 2D Matrix value passed to shader
 */
void Shader::SetMat2(const std::string& name, glm::mat2& value) const {
    glUseProgram(handle);
    glUniformMatrix2fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 3D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 3D Matrix value passed to shader
 */
void Shader::SetMat3(const std::string& name, glm::mat3& value) const {
    glUseProgram(handle);
    glUniformMatrix3fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 4D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 4D Matrix value passed to shader
 */
void Shader::SetMat4(const std::string& name, glm::mat4& value) const {
    glUseProgram(handle);
    glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}