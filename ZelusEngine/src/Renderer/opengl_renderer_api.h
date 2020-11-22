#pragma once
#include "renderer_api.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
	virtual void SetClearColour(const glm::vec4& colour) override;

	virtual void Clear() override;

	virtual void CullBackFaces() override;

	virtual void DrawIndexed(Renderable* renderable, Camera* cam) override;

};

