#pragma once

#include "renderer_api.h"
#include "shader.h"
#include "transform.h"

class RenderCommands {
public:

	inline static void SetClearColour(const glm::vec4& colour) {
		sAPI->SetClearColour(colour);
	}

	inline static void Clear() {
		sAPI->Clear();
	}

	inline static void CullBackFaces() {
		sAPI->CullBackFaces();
	}

	inline static void DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> camera) {
		sAPI->DrawIndexed(renderable, transform, shader, camera);
	}
private: 

	static RendererAPI* sAPI;
};