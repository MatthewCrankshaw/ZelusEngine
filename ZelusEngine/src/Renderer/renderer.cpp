#include "renderer.h"
#include "transform.h"

Ref<Camera> Renderer::sCamera = nullptr;

void Renderer::BeginScene(Ref<Camera> camera) {
	sCamera = camera;
}

void Renderer::RenderScene() {
	if (sCamera == nullptr) {
		gLog->AddLog("[ERROR] BeginScene in Renderer is not called before RenderScene");
	}
	//TODO Here we want to render the scene in the correct order 
	entt::basic_view view = gECM->mRegistry.view<EntityType, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : view) {

		EntityType type = view.get<EntityType>(entity);
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		switch (type) {
			case EntityType::REGULAR:
				RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
				break;
			case EntityType::DEFERRED:
				RenderDeferredScene(renderable, transform, shader);
				break;
			case EntityType::AXIS:
				RenderAxis(renderable, transform, shader);
				break;
			case EntityType::SKYBOX:
				RenderSkybox(renderable, transform, shader);
				break;
			case EntityType::LIGHTING_PASS:
				RenderLightingPass(renderable, transform, shader);
				break;
		}
	}
}

void Renderer::RenderDeferredScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::RenderSkybox(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	shader->Use();

	glm::vec3 position;
	sCamera->GetPosition(position);
	transform->SetPosition(position);

	glm::mat4 model = transform->GetModelTransform();
	glm::mat4 view = sCamera->GetViewMatrix();
	glm::mat4 projection = sCamera->GetProjectionMatrix();
	

	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);

	shader->UnUse();
}

void Renderer::RenderAxis(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::RenderLightingPass(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::EndScene() {
}