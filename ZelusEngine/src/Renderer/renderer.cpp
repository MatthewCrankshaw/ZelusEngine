#include "renderer.h"

std::vector<Renderable*> Renderer::sRenderables;
Camera* Renderer::sCamera;

void Renderer::BeginScene(Camera* camera) {
	sCamera = camera;
	sRenderables.clear();
}

void Renderer::EndScene() {
	for(int i = 0; i < sRenderables.size(); i++){
		//gLog->AddLog(("Item Position: " + glm::to_string(sRenderables[i]->GetPosition())).c_str());
		glm::vec3 pos; 
		sCamera->GetPosition(pos);
		sRenderables[i]->Draw(*sCamera);
	}
}

void Renderer::Submit(Renderable* renderable) {
	sRenderables.push_back(renderable);
}