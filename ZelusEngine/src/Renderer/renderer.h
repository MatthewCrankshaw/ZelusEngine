#pragma once

#include "render_commands.h"
#include "../log.h"
#include "../entity_component_manager.h"
#include "../ref.h"

extern Log* gLog;
extern EntityComponentManager* gECM;

class Renderer
{
private: 
	Ref<Camera> mCamera;
public: 
	static void BeginScene(); 

	static void EndDeferredScene(Ref<Camera> camera);

	static void EndScene();
};

