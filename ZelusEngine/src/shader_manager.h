#pragma once
#include "ref.h"
#include "shader.h"

class ShaderManager
{
private:
	Ref<Shader> basicShader = nullptr;
	Ref<Shader> multiLightShader = nullptr;
	Ref<Shader> skyBoxShader = nullptr;
	Ref<Shader> axisShader = nullptr;
	Ref<Shader> geometricPassShader = nullptr;
	Ref<Shader> lightingPassShader = nullptr;
	Ref<Shader> hdrShader = nullptr;
public:

	void StartUp();

	void ShutDown();

	Ref<Shader> getBasicShader() {
		if (basicShader == nullptr) {
			basicShader = Ref<Shader>(new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl"));
		}
		return basicShader;
	}

	Ref<Shader> getMultiLightShader() {
		if (multiLightShader == nullptr) {
			multiLightShader = Ref<Shader>(new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl"));
		}
		return multiLightShader;
	}

	Ref<Shader> getSkyBoxShader() {
		if(skyBoxShader == nullptr){
			skyBoxShader = Ref<Shader>(new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl"));
		}
		return skyBoxShader;
	}

	Ref<Shader> getAxisShader() {
		if (axisShader == nullptr) {
			axisShader = Ref<Shader>(new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl"));
		}
		
		return axisShader;
	}

	Ref<Shader> getGeometryPassShader() {
		if (geometricPassShader == nullptr) {
			geometricPassShader = Ref<Shader>(new Shader("Shaders/geometric_pass_vertex.glsl", "Shaders/geometric_pass_fragment.glsl"));
		}
		
		return geometricPassShader;
	}

	Ref<Shader> getLighthingPassShader() {
		if (lightingPassShader == nullptr) {
			lightingPassShader = Ref<Shader>(new Shader("Shaders/lighting_pass_vertex.glsl", "Shaders/lighting_pass_fragment.glsl"));
		}
		
		return lightingPassShader;
	}

	Ref<Shader> getHDRShader() {
		if (hdrShader == nullptr) {
			hdrShader = Ref<Shader>(new Shader("Shaders/hdr_vertex.glsl", "Shaders/hdr_fragment.glsl"));
		}
		
		return hdrShader;
	}
};

