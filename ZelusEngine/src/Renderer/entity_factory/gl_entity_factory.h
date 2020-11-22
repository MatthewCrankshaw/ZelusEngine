#pragma once
#include <entt/entt.hpp>

#include "abstract_entity_factory.h"
#include "../../entity_component_manager.h"
#include "../gl_api/sky_box.h"
#include "../gl_api/cube.h"

extern EntityComponentManager* gECM;

class GlEntityFactory : public AbstractEntityFactory
{
public:
	// Inherited via AbstractEntityFactory
	virtual entt::entity CreateCubeEntity() const override;
};

