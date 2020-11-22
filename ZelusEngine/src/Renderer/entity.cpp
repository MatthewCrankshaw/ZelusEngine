#include "entity.h"

Entity::Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, Ref<Transform> transform, bool deferredShading)
{
	mName = name;
	mRenderable = renderable;
	mCamera = camera;
	mTransform = transform;
	mDeferredShading = deferredShading;
}

Entity::Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, bool deferredShading){
	mName = name; 
	mRenderable = renderable; 
	mCamera = camera;
	mTransform = Ref<Transform>(new Transform());
	mDeferredShading = deferredShading;
}

void Entity::Draw(){ 
	
	glm::mat4 model = mTransform->GetModelTransform();

	mRenderable->SetModelMat(model);
	mRenderable->Draw(mCamera);

}

void Entity::Update(){ 

}