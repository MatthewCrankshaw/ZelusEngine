#include "shader_manager.h"

void ShaderManager::StartUp()
{
	basicShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");
	multiLightShader = new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
	skyBoxShader = new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
	axisShader = new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
	geometricPassShader = new Shader("Shaders/geometric_pass_vertex.glsl", "Shaders/geometric_pass_fragment.glsl");
	lightingPassShader = new Shader("Shaders/lighting_pass_vertex.glsl", "Shaders/lighting_pass_fragment.glsl");
	hdrShader = new Shader("Shaders/hdr_vertex.glsl", "Shaders/hdr_fragment.glsl");
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
