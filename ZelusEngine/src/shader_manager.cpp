#include "shader_manager.h"

void ShaderManager::StartUp()
{
	mShaders = Ref<std::map<enum ShaderType, Ref<Shader>>>(new std::map<enum ShaderType, Ref<Shader>>());
}

void ShaderManager::ShutDown()
{
}
