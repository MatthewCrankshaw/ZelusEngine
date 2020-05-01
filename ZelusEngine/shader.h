#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>


class Shader
{
public: 
	Shader(const std::string &vertexShader, const std::string &fragmentShader); 
	~Shader(); 

	void Use(); 
	void UnUse();

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, glm::vec2& value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, glm::vec3& value) const;
    void SetVec3(const std::string& name, glm::vec4& value) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, glm::vec4& value) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const std::string& name, glm::mat2& value) const;
    void SetMat3(const std::string& name, glm::mat3& value) const;
    void SetMat4(const std::string& name, glm::mat4& value) const;

private:
    enum ProgramType {VERTEX, FRAGMENT, PROGRAM};

	GLuint handle;

    static char* ReadShaderFiles(const std::string& filename);
    static void CheckCompileErrors(GLuint shader, ProgramType type);

};

