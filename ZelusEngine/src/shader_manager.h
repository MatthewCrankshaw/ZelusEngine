#pragma once
#include "shader.h"

class ShaderManager
{
private:
	Shader* basicShader = nullptr;
	Shader* multiLightShader = nullptr;
	Shader* skyBoxShader = nullptr;
	Shader* axisShader = nullptr;
	Shader* geometricPassShader = nullptr;
	Shader* lightingPassShader = nullptr;
	Shader* hdrShader = nullptr;
public:

	void StartUp();

	void ShutDown();

	Shader* getBasicShader() {
		if (basicShader == nullptr) {
			basicShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");
		}
		return basicShader;
	}

	Shader* getMultiLightShader() {
		if (multiLightShader == nullptr) {
			multiLightShader = new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
		}
		return multiLightShader;
	}

	Shader* getSkyBoxShader() {
		if(skyBoxShader == nullptr){
			skyBoxShader = new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
		}
		return skyBoxShader;
	}

	Shader* getAxisShader() {
		if (axisShader == nullptr) {
			axisShader = new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
		}
		
		return axisShader;
	}

	Shader* getGeometryPassShader() {
		if (geometricPassShader == nullptr) {
			geometricPassShader = new Shader("Shaders/geometric_pass_vertex.glsl", "Shaders/geometric_pass_fragment.glsl");
		}
		
		return geometricPassShader;
	}

	Shader* getLighthingPassShader() {
		if (lightingPassShader == nullptr) {
			lightingPassShader = new Shader("Shaders/lighting_pass_vertex.glsl", "Shaders/lighting_pass_fragment.glsl");
		}
		
		return lightingPassShader;
	}

	Shader* getHDRShader() {
		if (hdrShader == nullptr) {
			hdrShader = new Shader("Shaders/hdr_vertex.glsl", "Shaders/hdr_fragment.glsl");
		}
		
		return hdrShader;
	}
};

