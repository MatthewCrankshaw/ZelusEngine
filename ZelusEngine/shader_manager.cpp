#include "shader_manager.h"

void ShaderManager::StartUp()
{
	basicShader = new Shader("Shaders/basic_shader_vertex.glsl", "Shaders/basic_shader_fragment.glsl");
	multiLightShader = new Shader("Shaders/multi_light_vertex.glsl", "Shaders/multi_light_fragment.glsl");
	skyBoxShader = new Shader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
	axisShader = new Shader("Shaders/axis_vertex.glsl", "Shaders/axis_fragment.glsl");
}

void ShaderManager::ShutDown()
{
}
