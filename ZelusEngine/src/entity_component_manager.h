#pragma once
#include <entt/entt.hpp>
#include "renderer/renderable.h"

class EntityComponentManager
{
public:
	entt::registry mRegistry;

	void StartUp();
	void ShutDown();

	void AddRenderable(Ref<Renderable> renderable);
};

