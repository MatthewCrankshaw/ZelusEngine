#include "renderer.h"

void Renderer::BeginScene() {
}

void Renderer::EndScene() {

}

void Renderer::Submit(Renderable* renderable, Camera* camera) {
	renderable->Draw(*camera);
}