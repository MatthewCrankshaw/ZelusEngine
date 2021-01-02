#pragma once
#include "gl_renderable.h"
#include "../../renderer_api.h"

class GLRendererAPI : public RendererAPI
{
public:
	virtual void SetClearColour(const glm::vec4& colour) override;

	virtual void Clear() override;

	virtual void CullBackFaces() override;

	virtual void EnableDepthTest() override;

	virtual void DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> cam) override;

	virtual void SetTexture(Ref<Shader> shader, Ref<Texture> texture) override;

};

