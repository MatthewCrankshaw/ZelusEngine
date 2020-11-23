#include "renderer.h"

std::vector<Ref<Entity>> Renderer::sEntities;

void Renderer::BeginScene() {
	sEntities.clear();
}

void Renderer::EndDeferredScene() {
	for(size_t i = 0; i < sEntities.size(); i++){
		if(sEntities[i]->IsDeferredShading()){
			sEntities[i]->Draw();
		}
	}
}

void Renderer::EndScene()
{
	for (size_t i = 0; i < sEntities.size(); i++) {
		if (!sEntities[i]->IsDeferredShading()) {
			sEntities[i]->Draw();
		}
	}
}

void Renderer::Submit(Ref<Entity> entity) {
	sEntities.push_back(entity);
}