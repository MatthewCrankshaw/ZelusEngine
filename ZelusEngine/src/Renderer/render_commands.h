#pragma once

#include "renderer_api.h"

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

	inline static void DrawIndexed(Renderable* renderable, Camera* camera) {
		sAPI->DrawIndexed(renderable, camera);
	}
private: 

	static RendererAPI* sAPI;
};