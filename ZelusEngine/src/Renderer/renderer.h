#pragma once

#include "render_commands.h"

class Renderer
{
public: 
	static void BeginScene(); 

	static void EndScene();

	static void Submit(Renderable* renderable, Camera* camera);

private:
};

