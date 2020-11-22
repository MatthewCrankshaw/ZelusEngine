#include "gl_entity_factory.h"

entt::entity GlEntityFactory::CreateCubeEntity() const
{
	auto cubeEntity = gECM->mRegistry.create();
	gECM->mRegistry.emplace<Ref<Renderable>>(cubeEntity, new Cube());
	return cubeEntity;
}
