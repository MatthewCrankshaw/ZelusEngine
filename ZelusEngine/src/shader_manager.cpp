#include "shader_manager.h"

void ShaderManager::StartUp()
{
}

void ShaderManager::ShutDown()
{
	delete basicShader;
	delete multiLightShader;
	delete skyBoxShader;
	delete axisShader;
	delete geometricPassShader;
	delete lightingPassShader;
	delete hdrShader;
}
