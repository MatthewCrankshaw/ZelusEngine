#pragma once
#include "gl_renderable.h"
#include "../../renderer_api.h"

class GLRendererAPI : public RendererAPI
{
public:
	virtual void SetClearColour(const glm::vec4& colour) override;

	virtual void Clear() override;

	virtual void CullBackFaces() override;

	virtual void DrawIndexed(Ref<Renderable> renderable, Ref<Camera> cam) override;

};

