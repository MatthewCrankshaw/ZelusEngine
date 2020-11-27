#include "renderer.h"

void Renderer::BeginScene() {
}

void Renderer::EndDeferredScene(Ref<Camera> camera) {
	entt::basic_view view = gECM->mRegistry.view<Ref<Renderable>>();

	for (auto entity : view) {
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		RenderCommands::DrawIndexed(renderable, camera);
	}
}

void Renderer::EndScene() {
}