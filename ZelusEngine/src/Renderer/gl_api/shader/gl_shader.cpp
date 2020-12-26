#include "gl_shader.h"

/*!
 * Destructor of the shader object
 * @details - will remove all shader objects
 */
GLShader::~GLShader() {
    glDeleteShader(mHandle);
    gLog->AddLog("[info] Shaders Deleted: %s and %s", mVertexPath.c_str(), mFragmentPath.c_str());
}

/*!
 * Use this objects shader program {glUseProgram(mHandle)}
 * @return void
 */
void GLShader::Use() {
    glUseProgram(mHandle);
}

/*!
 * Stop using this objects shader program {glUseProgram(0)}
 * @return void
 */
void GLShader::UnUse() {
    glUseProgram(0);
}

void GLShader::LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    mVertexPath = vertexShaderPath;
    mFragmentPath = fragmentShaderPath;
    char* vertexShaderString;
    char* fragmentShaderString;

    vertexShaderString = ReadShaderFiles(mVertexPath);
    fragmentShaderString = ReadShaderFiles(mFragmentPath);

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

    mHandle = glCreateProgram();
    glAttachShader(mHandle, vertexHandle);
    glAttachShader(mHandle, fragmentHandle);

    glLinkProgram(mHandle);

    glGetShaderiv(mHandle, GL_INFO_LOG_LENGTH, &logLength);
    glGetShaderiv(mHandle, GL_LINK_STATUS, &success);

    if (!success) {
        str = new char[logLength];
        glGetShaderInfoLog(mHandle, logLength, NULL, str);
        std::cout << str << std::endl;
        delete[] str;
    }

    glDeleteShader(vertexHandle);
    glDeleteShader(fragmentHandle);

    free(vertexShaderString);
    free(fragmentShaderString);

    gLog->AddLog("[info] Shaders Loaded: %s and %s", mVertexPath.c_str(), mFragmentPath.c_str());
}

/*!
 * Create a uniform location and value for a boolean inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - Boolean value passed to the shader
 */
void GLShader::SetBool(const std::string& name, bool value) const {
    glUseProgram(mHandle);
    glUniform1i(glGetUniformLocation(mHandle, name.c_str()), (int)value);
}

/*!
 * Create a uniform location and value for a integer inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - Integer value passed to the shader
 */
void GLShader::SetInt(const std::string& name, int value) const {
    glUseProgram(mHandle);
    glUniform1i(glGetUniformLocation(mHandle, name.c_str()), value);
}

/*!
 * Create a uniform location and value for a float inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value
 */
void GLShader::SetFloat(const std::string& name, float value) const {
    glUseProgram(mHandle);
    glUniform1f(glGetUniformLocation(mHandle, name.c_str()), value);
}

/*!
 * Create a uniform location and value for a 2D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 2D Vector value passed to the shader
 */
void GLShader::SetVec2(const std::string& name, glm::vec2& value) const {
    glUseProgram(mHandle);
    glUniform2fv(glGetUniformLocation(mHandle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 2D Vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of X passed to the shader
 * @param y - Value of Y passed to the shader
 */
void GLShader::SetVec2(const std::string& name, float x, float y) const {
    glUseProgram(mHandle);
    glUniform2f(glGetUniformLocation(mHandle, name.c_str()), x, y);
}

/*!
 * Create a uniform location and value for a 3D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 3D Vector value passed to the shader
 */
void GLShader::SetVec3(const std::string& name, glm::vec3& value) const {
    glUseProgram(mHandle);
    glUniform3fv(glGetUniformLocation(mHandle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 3D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of x passed to the shader
 * @param y - Value of y passed to the shader
 * @param z - Value of z passed to the shader
 */
void GLShader::SetVec3(const std::string& name, float x, float y, float z) const {
    glUseProgram(mHandle);
    glUniform3f(glGetUniformLocation(mHandle, name.c_str()), x, y, z);
}

/*!
 * Create a uniform location and value for a 3D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 4D Vector value passed to shader this will be parsed to be 3D
 */
void GLShader::SetVec3(const std::string& name, glm::vec4& value) const {
    glUseProgram(mHandle);
    glUniform3fv(glGetUniformLocation(mHandle, name.c_str()), 1, glm::value_ptr(glm::vec3(value)));
}

/*!
 * Create a uniform location and value for a 4D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 4D Vector value passed to the shader
 */
void GLShader::SetVec4(const std::string& name, glm::vec4& value) const {
    glUseProgram(mHandle);
    glUniform4fv(glGetUniformLocation(mHandle, name.c_str()), 1, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 4D vector inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param x - Value of x passed to the shader
 * @param y - Value of x passed to the shader
 * @param z - Value of x passed to the shader
 * @param w - Value of x passed to the shader
 */
void GLShader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    glUseProgram(mHandle);
    glUniform4f(glGetUniformLocation(mHandle, name.c_str()), x, y, z, w);
}

/*!
 * Create a uniform location and value for a 2D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 2D Matrix value passed to shader
 */
void GLShader::SetMat2(const std::string& name, glm::mat2& value) const {
    glUseProgram(mHandle);
    glUniformMatrix2fv(glGetUniformLocation(mHandle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 3D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 3D Matrix value passed to shader
 */
void GLShader::SetMat3(const std::string& name, glm::mat3& value) const {
    glUseProgram(mHandle);
    glUniformMatrix3fv(glGetUniformLocation(mHandle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/*!
 * Create a uniform location and value for a 4D Matrix inside this shader program
 * @param name - Name of the location, used in the shader program
 * @param value - 4D Matrix value passed to shader
 */
void GLShader::SetMat4(const std::string& name, glm::mat4& value) const {
    glUseProgram(mHandle);
    glUniformMatrix4fv(glGetUniformLocation(mHandle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}