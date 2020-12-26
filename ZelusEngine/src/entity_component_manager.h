#pragma once
#include <entt/entt.hpp>
#include "renderer/renderable.h"
#include "renderer/shader.h"
#include "renderer/gl_api/shader/gl_shader.h"
#include "shader_manager.h"

enum class EntityType {
	GEOMETRIC_PASS,
	LIGHTING_PASS, 
	DEFERRED,
	REGULAR,
	SKYBOX,
	AXIS
};

extern ShaderManager* gShaderManager;

class EntityComponentManager
{
public:
	entt::registry mRegistry;

	void StartUp();
	void ShutDown();

	void AddRegularEntity(Ref<Renderable> renderable);
	void AddDeferredEntity(Ref<Renderable> renderable);
	void AddSkyboxEntity(Ref<Renderable> renderable);
	void AddAxisEntity(Ref<Renderable> renderable);
	void AddLightingPassEntity(Ref<Renderable> renderable);
};

