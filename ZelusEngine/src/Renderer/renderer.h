#pragma once

#include "render_commands.h"
#include "../log.h"

extern Log* gLog;

class Renderer
{
public: 
	static void BeginScene(Camera* camera); 

	static void EndScene();

	static void Submit(Renderable* renderable);

	static inline std::vector<Renderable*> GetEntities(){
		return sRenderables;
	}

private:
	static Camera* sCamera;
	static std::vector<Renderable*> sRenderables;
};

