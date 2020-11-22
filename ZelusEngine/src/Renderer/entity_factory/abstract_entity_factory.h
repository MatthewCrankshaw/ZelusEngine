#pragma once
#include <entt/entt.hpp>

#include "../gl_api/cube.h"

class AbstractEntityFactory
{
public:
	virtual entt::entity CreateCubeEntity() const = 0;
};

