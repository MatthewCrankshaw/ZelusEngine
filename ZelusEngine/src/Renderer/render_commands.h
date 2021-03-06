#pragma once

#include "renderer_api.h"
#include "shader.h"
#include "transform.h"
#include "gl_api/renderables/gl_renderer_api.h"

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

	inline static void EnableDepthTest() {
		sAPI->EnableDepthTest();
	}

	inline static void DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> camera) {
		shader->Use();
		sAPI->DrawIndexed(renderable, transform, shader, camera);
		shader->UnUse();
	}

	inline static void SetSingleTexture(Ref<Shader> shader, Ref<Texture> texture) {
		sAPI->SetSingleTexture(shader, texture);
	}

	inline static void SetCubeMapTexture(Ref<Shader> shader, Ref<Texture> texture) {
		sAPI->SetCubeMapTexture(shader, texture);
	}
private: 

	static RendererAPI* sAPI;
};