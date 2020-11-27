#include "entity_component_manager.h"
#include "renderer/transform.h"

void EntityComponentManager::StartUp()
{
}

void EntityComponentManager::ShutDown()
{
}

void EntityComponentManager::AddRenderable(Ref<Renderable> renderable)
{
	Ref<Transform> transform(new Transform());
	auto entity = mRegistry.create();
	mRegistry.emplace<Ref<Renderable>>(entity, renderable);
	mRegistry.emplace<Ref<Transform>>(entity, transform);
}
