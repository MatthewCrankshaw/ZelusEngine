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
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::RenderAxis(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::RenderLightingPass(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
}

void Renderer::EndScene() {
}