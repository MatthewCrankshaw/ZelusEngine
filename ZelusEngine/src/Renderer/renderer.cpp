#include "renderer.h"
#include "transform.h"

void Renderer::BeginScene() {
}

void Renderer::EndDeferredScene(Ref<Camera> camera) {
	entt::basic_view view = gECM->mRegistry.view<Ref<Renderable>, Ref<Transform>>();

	for (auto entity : view) {
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		RenderCommands::DrawIndexed(renderable, camera);
	}
}

void Renderer::EndScene() {
}