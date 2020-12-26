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
	static Ref<Camera> sCamera;

	static void RenderDeferredScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderSkybox(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderAxis(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderLightingPass(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);

public: 
	static void BeginScene(Ref<Camera> camera);

	static void RenderScene();

	static void EndScene();
};

