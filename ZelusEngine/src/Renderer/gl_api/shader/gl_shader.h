#pragma once

#include "../../shader.h"

class GLShader : public Shader
{
public:
	~GLShader(); 

	void Use() override; 
	void UnUse() override;

    void LoadShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) override;

    void SetBool(const std::string& name, bool value) const override;
    void SetInt(const std::string& name, int value) const override;
    void SetFloat(const std::string& name, float value) const override;
    void SetVec2(const std::string& name, glm::vec2& value) const override;
    void SetVec2(const std::string& name, float x, float y) const override;
    void SetVec3(const std::string& name, glm::vec3& value) const override;
    void SetVec3(const std::string& name, glm::vec4& value) const override;
    void SetVec3(const std::string& name, float x, float y, float z) const override;
    void SetVec4(const std::string& name, glm::vec4& value) const override;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const override;
    void SetMat2(const std::string& name, glm::mat2& value) const override;
    void SetMat3(const std::string& name, glm::mat3& value) const override;
    void SetMat4(const std::string& name, glm::mat4& value) const override;
};

