#pragma once
#include <entt/entt.hpp>
#include "renderer/renderable.h"
#include "renderer/shader.h"
#include "renderer/gl_api/shader/gl_shader.h"
#include "shader_manager.h"
#include "renderer/transform.h"
#include "renderer/texture.h"
#include "renderer/texture_factory/gl_texture_factory.h"
#include "../meta_data.h"

extern Ref<ShaderManager> gShaderManager;

class EntityComponentManager
{
private:
	entt::registry mRegistry;
	entt::entity mHDRBuffer;
	entt::entity mLightingBuffer;
public:
	void StartUp();
	void ShutDown();

	inline entt::registry& GetRegistry() {
		return mRegistry;
	}

	inline entt::entity& GetHDRBuffer() {
		return mHDRBuffer;
	}

	inline entt::entity& GetLightingBuffer() {
		return mLightingBuffer;
	}

	inline bool HasTexture(entt::entity entity) {
		return mRegistry.has<Ref<Texture>>(entity);
	}

	inline Ref<Texture> GetTexture(entt::entity entity) {
		return mRegistry.get<Ref<Texture>>(entity);
	}

	inline bool HasTransforms(entt::entity entity) {
		return mRegistry.has<Ref<Transform>>(entity);
	}

	inline Ref<Transform> GetTransform(entt::entity entity) {
		return mRegistry.get<Ref<Transform>>(entity);
	}

	inline Ref<MetaData> GetMetaData(entt::entity entity) {
		return mRegistry.get<Ref<MetaData>>(entity);
	}

	void AddRegularEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture);
	void AddDeferredEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture = nullptr);
	void AddSkyboxEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture);
	void AddAxisEntity(std::string name, Ref<Renderable> renderable);
	void AddLightingPassEntity(std::string name, Ref<Renderable> renderable);
	void AddHdrBufferEntity(std::string name, Ref<Renderable> renderable, Ref<Texture> texture);
};

