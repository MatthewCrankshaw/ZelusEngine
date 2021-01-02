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

void GLRendererAPI::EnableDepthTest()
{
	glEnable(GL_DEPTH_TEST);
}

void GLRendererAPI::DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> camera)
{
	renderable->Draw(camera);
}

void GLRendererAPI::SetTexture(Ref<Shader> shader, Ref<Texture> texture) 
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
}