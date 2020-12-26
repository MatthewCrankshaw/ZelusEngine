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

void GLRendererAPI::DrawIndexed(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader, Ref<Camera> camera)
{
	//shader->Use();

	//glm::mat4 projection = camera->GetProjectionMatrix();
	//glm::mat4 view = camera->GetViewMatrix();
	//glm::mat4 model = transform->GetModelTransform();

	//shader->SetMat4("projection", projection);
	//shader->SetMat4("view", view);
	//shader->SetMat4("model", model);

	renderable->Draw(camera);

	//shader->UnUse();
}
