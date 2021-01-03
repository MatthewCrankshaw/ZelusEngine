#include "entity_component_manager.h"

void EntityComponentManager::StartUp()
{
}

void EntityComponentManager::ShutDown()
{
}

void EntityComponentManager::AddRegularEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::REGULAR));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::BASIC);

	auto entity = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(entity, data);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);

	if (texture != nullptr) {
		mRegistry.emplace<Ref<Texture>>(entity, texture);
	}
}

void EntityComponentManager::AddDeferredEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::DEFERRED_GEOMETRY));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::GEOMETRY_PASS);

	auto entity = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(entity, data);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);

	if (texture != nullptr) {
		mRegistry.emplace<Ref<Texture>>(entity, texture);
	}
}

void EntityComponentManager::AddSkyboxEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::SKYBOX));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::SKYBOX);

	auto entity = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(entity, data);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);
	mRegistry.emplace<Ref<Texture>>(entity, texture);
}

void EntityComponentManager::AddAxisEntity(std::string name, Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::AXIS));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::AXIS_SHADER);

	auto entity = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(entity, data);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);
}

void EntityComponentManager::AddLightingPassEntity(std::string name, Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::DEFERRED_LIGHTING));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::DEFERRED_LIGHTING);

	mLightingBuffer = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(mLightingBuffer, data);
	mRegistry.emplace<Ref<Renderable>>(mLightingBuffer, renderable);
	mRegistry.emplace<Ref<Shader>>(mLightingBuffer, shader);
}

void EntityComponentManager::AddHdrBufferEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<MetaData> data(new MetaData(name, EntityType::HDR_PASS));
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::HDR);

	mHDRBuffer = mRegistry.create();
	mRegistry.emplace<Ref<MetaData>>(mHDRBuffer, data);
	mRegistry.emplace<Ref<Renderable>>(mHDRBuffer, renderable);
	mRegistry.emplace<Ref<Shader>>(mHDRBuffer, shader);
	mRegistry.emplace<Ref<Texture>>(mHDRBuffer, texture);
}
