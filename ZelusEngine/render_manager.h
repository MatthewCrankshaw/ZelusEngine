#pragma once

#include <vector>

#include "renderable.h"
#include "model.h"

class RenderManager
{
public: 
	RenderManager(Camera* camera);

	void Render();

	void Add(Renderable* rend);
private:
	Camera* mCamera;
	std::vector<Renderable*> renderList;
};

