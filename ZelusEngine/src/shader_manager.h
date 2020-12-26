#pragma once

#include <map>

#include "ref.h"
#include "renderer/gl_api/shader/gl_shader.h"

enum class ShaderType {
		BASIC,
		MULTI_LIGHT, 
		SKYBOX,
		AXIS_SHADER,
		GEOMETRY_PASS, 
		LIGHTING_PASS, 
		HDR
};

class ShaderManager
{
private:

	Ref<std::map<enum ShaderType, Ref<Shader>>> mShaders;
public:

	void StartUp();

	void ShutDown();

	Ref<Shader> GetShader(enum ShaderType type) {
		switch (type) {
		case ShaderType::BASIC: 
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::MULTI_LIGHT:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::SKYBOX:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::AXIS_SHADER:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::GEOMETRY_PASS:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/geometric_pass_vertex.glsl", "Shaders/geometric_pass_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::LIGHTING_PASS:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/lighting_pass_vertex.glsl", "Shaders/lighting_pass_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		case ShaderType::HDR:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/hdr_vertex.glsl", "Shaders/hdr_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		default:
			if (mShaders->find(type) == mShaders->end()) {
				mShaders->emplace(type, Ref<GLShader>(new GLShader()));
				mShaders->at(type)->LoadShader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");
				return mShaders->at(type);
			}
			else {
				return mShaders->at(type);
			}
		}
	}
};

