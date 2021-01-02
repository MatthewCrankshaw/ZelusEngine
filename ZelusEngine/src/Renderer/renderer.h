#pragma once
#include "../user_interface.h"
#include "../log.h"
#include "../entity_component_manager.h"
#include "transform.h"
#include "texture.h"
#include "render_commands.h"

extern Ref<UserInterface> gUserInterface;
extern Ref<Log> gLog;
extern Ref<EntityComponentManager> gECM;

class Renderer
{
private: 
	static Ref<Camera> sCamera;
	static std::vector<entt::entity> sDeferredEntityQueue;
	static std::vector<entt::entity> sRegularEntityQueue;

	static void RenderDeferredScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderSkybox(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderAxis(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderLightingPass(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderHDRPass(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);
	static void RenderRegularScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader);

public: 
	static void BeginScene(Ref<Camera> camera);

	static void RenderDeferredGeometryBuffer();
	static void RenderDeferredLightingBuffer();
	static void RenderHDRBuffer();
	static void RenderRegularBuffer();

	static void EndScene();
};

