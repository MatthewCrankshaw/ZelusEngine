#include "opengl_renderer_api.h"

void OpenGLRendererAPI::SetClearColour(const glm::vec4& colour)
{
	glClearColor(colour.r, colour.g, colour.b, colour.a);
}

void OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLRendererAPI::CullBackFaces()
{
	glCullFace(GL_BACK);
}

void OpenGLRendererAPI::DrawIndexed(Ref<Renderable> renderable, Ref<Camera> camera)
{
	renderable->Draw(camera);
}
