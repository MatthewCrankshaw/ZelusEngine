#pragma once
#include <entt/entt.hpp>
#include "renderer/renderable.h"
#include "renderer/shader.h"
#include "renderer/gl_api/shader/gl_shader.h"
#include "shader_manager.h"
#include "renderer/transform.h"

enum class EntityType {
	DEFERRED_LIGHTING,
	DEFERRED_GEOMETRY,
	HDR_PASS,
	REGULAR,
	SKYBOX,
	AXIS
};

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

	void AddRegularEntity(Ref<Renderable> renderable);
	void AddDeferredEntity(Ref<Renderable> renderable);
	void AddSkyboxEntity(Ref<Renderable> renderable);
	void AddAxisEntity(Ref<Renderable> renderable);
	void AddLightingPassEntity(Ref<Renderable> renderable);
	void AddHdrBufferEntity(Ref<Renderable> renderable);
};

