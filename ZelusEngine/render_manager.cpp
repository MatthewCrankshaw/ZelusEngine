#include "render_manager.h"


RenderManager::RenderManager(Camera *camera) {
	mCamera = camera;
}

void RenderManager::Render()
{
	for (auto item : renderList) {
		item->Draw(*mCamera);
	}
}

void RenderManager::Add(Renderable* rend) {
	renderList.push_back(rend);
}