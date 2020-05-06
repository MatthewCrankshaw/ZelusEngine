#pragma once
#include "shader.h"

class ShaderManager
{
private:
	Shader* basicShader;
	Shader* multiLightShader;
	Shader* skyBoxShader;
	Shader* axisShader;
	Shader* geometricPassShader;
	Shader* lightingPassShader;
	Shader* hdrShader;
public:

	void StartUp();

	void ShutDown();

	Shader* getBasicShader() {
		return basicShader;
	}

	Shader* getMultiLightShader() {
		return multiLightShader;
	}

	Shader* getSkyBoxShader() {
		return skyBoxShader;
	}

	Shader* getAxisShader() {
		return axisShader;
	}

	Shader* getGeometryPassShader() {
		return geometricPassShader;
	}

	Shader* getLighthingPassShader() {
		return lightingPassShader;
	}

	Shader* getHDRShader() {
		return hdrShader;
	}
};

