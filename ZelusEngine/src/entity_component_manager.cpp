#include "entity_component_manager.h"

void EntityComponentManager::StartUp()
{
}

void EntityComponentManager::ShutDown()
{
}

void EntityComponentManager::AddRegularEntity(Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::BASIC);

	auto entity = mRegistry.create();
	mRegistry.emplace<EntityType>(entity, EntityType::REGULAR);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);
}

void EntityComponentManager::AddDeferredEntity(Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::GEOMETRY_PASS);

	auto entity = mRegistry.create();
	mRegistry.emplace<EntityType>(entity, EntityType::DEFERRED_GEOMETRY);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);

	if (texture != nullptr) {
		mRegistry.emplace<Ref<Texture>>(entity, texture);
	}
}

void EntityComponentManager::AddSkyboxEntity(Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::SKYBOX);

	auto entity = mRegistry.create();
	mRegistry.emplace<EntityType>(entity, EntityType::SKYBOX);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);
}

void EntityComponentManager::AddAxisEntity(Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::AXIS_SHADER);

	auto entity = mRegistry.create();
	mRegistry.emplace<EntityType>(entity, EntityType::AXIS);
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
	mRegistry.emplace<Ref<Shader>>(entity, shader);
}

void EntityComponentManager::AddLightingPassEntity(Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::DEFERRED_LIGHTING);

	mLightingBuffer = mRegistry.create();
	mRegistry.emplace<EntityType>(mLightingBuffer, EntityType::DEFERRED_LIGHTING);
	mRegistry.emplace<Ref<Renderable>>(mLightingBuffer, renderable);
	mRegistry.emplace<Ref<Shader>>(mLightingBuffer, shader);
}

void EntityComponentManager::AddHdrBufferEntity(Ref<Renderable> renderable, Ref<Texture> texture)
{
	Ref<Transform> transform(new Transform());
	Ref<Shader> shader = gShaderManager->GetShader(ShaderType::HDR);

	mHDRBuffer = mRegistry.create();
	mRegistry.emplace<EntityType>(mHDRBuffer, EntityType::HDR_PASS);
	mRegistry.emplace<Ref<Renderable>>(mHDRBuffer, renderable);
	mRegistry.emplace<Ref<Shader>>(mHDRBuffer, shader);
	mRegistry.emplace<Ref<Texture>>(mHDRBuffer, texture);
}