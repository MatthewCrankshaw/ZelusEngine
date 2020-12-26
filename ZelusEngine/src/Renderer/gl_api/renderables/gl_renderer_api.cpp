#include "gl_renderer_api.h"

void GLRendererAPI::SetClearColour(const glm::vec4& colour)
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);
}

void GLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRendererAPI::CullBackFaces()
{
	glCullFace(GL_BACK);
}

void GLRendererAPI::DrawIndexed(Ref<Renderable> renderable, Ref<Camera> camera)
{
	renderable->Draw(camera);
}
