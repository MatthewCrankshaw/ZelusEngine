#include "entity.h"

Entity::Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera, Ref<Transform> transform)
{
	mName = name;
	mRenderable = renderable;
	mCamera = camera;
	mTransform = transform;
}

Entity::Entity(std::string name, Ref<Renderable> renderable, Ref<Camera> camera){
	mName = name; 
	mRenderable = renderable; 
	mCamera = camera;
	mTransform = Ref<Transform>(new Transform());
}

void Entity::Draw(){ 
	//Shader shader("Shaders/geometric_pass_vertex.glsl", "Shaders/geometric_pass_fragment.glsl");
	
	glm::mat4 model = mTransform->GetModelTransform();
	glm::mat4 view = mCamera->GetViewMatrix();
	glm::mat4 projection = mCamera->GetProjectionMatrix();

	//shader.Use();

	//shader.SetMat4("view", view);
	//shader.SetMat4("projection", projection);
	//shader.SetMat4("model", model);
	mRenderable->SetModelMat(model);
	mRenderable->SetViewMat(view);
	mRenderable->SetProjectionMat(projection);
	mRenderable->Draw(*mCamera);

	//shader.UnUse();
}

void Entity::Update(){ 

}