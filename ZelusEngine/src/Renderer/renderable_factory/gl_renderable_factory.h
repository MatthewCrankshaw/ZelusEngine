#pragma once
#include <entt/entt.hpp>

#include "abstract_renderable_factory.h"
#include "../../entity_component_manager.h"
#include "../gl_api/renderables/gl_rectangle.h"
#include "../gl_api/renderables/gl_sky_box.h"
#include "../gl_api/renderables/gl_cube.h"
#include "../gl_api/renderables/gl_model.h"

extern Ref<EntityComponentManager> gECM;

class GLRenderableFactory : public AbstractRenderableFactory
{
public:
	// Inherited via AbstractRenderableFactory
	virtual Ref<Renderable> CreateCube() const override;
	virtual Ref<Renderable> CreateModel(std::string path) const override;
	virtual Ref<Renderable> CreateRectangle() const override;
};

