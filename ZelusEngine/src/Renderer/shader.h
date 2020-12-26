#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "../ref.h"
#include "../log.h"

extern Ref<Log> gLog;

class Shader
{
protected: 
    std::string mVertexPath, mFragmentPath;
    GLuint mHandle = 0;

    static char* ReadShaderFiles(const std::string& filename);
public:
    enum class ProgramType { VERTEX, FRAGMENT, PROGRAM };

    virtual void Use() = 0;
    virtual void UnUse() = 0;

    virtual void LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) = 0;

    virtual void SetBool(const std::string& name, bool value) const = 0;
    virtual void SetInt(const std::string& name, int value) const = 0;
    virtual void SetFloat(const std::string& name, float value) const = 0;
    virtual void SetVec2(const std::string& name, glm::vec2& value) const = 0;
    virtual void SetVec2(const std::string& name, float x, float y) const = 0;
    virtual void SetVec3(const std::string& name, glm::vec3& value) const = 0;
    virtual void SetVec3(const std::string& name, glm::vec4& value) const = 0;
    virtual void SetVec3(const std::string& name, float x, float y, float z) const = 0;
    virtual void SetVec4(const std::string& name, glm::vec4& value) const = 0;
    virtual void SetVec4(const std::string& name, float x, float y, float z, float w) const = 0;
    virtual void SetMat2(const std::string& name, glm::mat2& value) const = 0;
    virtual void SetMat3(const std::string& name, glm::mat3& value) const = 0;
    virtual void SetMat4(const std::string& name, glm::mat4& value) const = 0;
};

