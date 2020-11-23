#pragma once
#include <entt/entt.hpp>

class AbstractEntityFactory
{
public:
	virtual entt::entity CreateCubeEntity() const = 0;
};

