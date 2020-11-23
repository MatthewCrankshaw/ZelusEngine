#include "gl_entity_factory.h"

entt::entity GLEntityFactory::CreateCubeEntity() const
{
	auto cubeEntity = gECM->mRegistry.create();
	gECM->mRegistry.emplace<Ref<GLRenderable>>(cubeEntity, new GLCube());
	return cubeEntity;
}
