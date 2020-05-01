#pragma once
#include "shader.h"

class ShaderManager
{
private:
	Shader* basicShader;
	Shader* multiLightShader;
	Shader* skyBoxShader;
	Shader* axisShader;
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
};

