#pragma once
#include <entt/entt.hpp>

class EntityComponentManager
{
public:
	entt::registry mRegistry;

	void StartUp();
	void ShutDown();
};

