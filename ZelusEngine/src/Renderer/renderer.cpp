#include "renderer.h"

Ref<Camera> Renderer::sCamera = nullptr;
std::vector<entt::entity> Renderer::sDeferredEntityQueue;
std::vector<entt::entity> Renderer::sRegularEntityQueue;

void Renderer::BeginScene(Ref<Camera> camera) {
	sCamera = camera;
	entt::basic_view view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Shader>>();

	for (auto entity : view) {
		EntityType type = view.get<EntityType>(entity);
		if (type == EntityType::DEFERRED_GEOMETRY) {
			sDeferredEntityQueue.push_back(entity);
		}
		else if (type == EntityType::REGULAR) {
			sRegularEntityQueue.push_back(entity);
		}
		else if (type == EntityType::SKYBOX || type == EntityType::AXIS) {
			sDeferredEntityQueue.push_back(entity);
		}
	}
}

void Renderer::RenderDeferredGeometryBuffer()
{
	entt::basic_view view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sDeferredEntityQueue) {
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);
		RenderDeferredScene(renderable, transform, shader);
	}
}

void Renderer::RenderDeferredLightingBuffer()
{
	auto view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Shader>>();

	EntityType type = view.get<EntityType>(gECM->GetLightingBuffer());
	Ref<Renderable> renderable = view.get<Ref<Renderable>>(gECM->GetLightingBuffer());
	Ref<Shader> shader = view.get<Ref<Shader>>(gECM->GetLightingBuffer());

	RenderLightingPass(renderable, shader);
}

void Renderer::RenderHDRBuffer(Ref<Texture> buffer)
{
	auto view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Shader>>();

	EntityType type = view.get<EntityType>(gECM->GetHDRBuffer());
	Ref<Renderable> renderable = view.get<Ref<Renderable>>(gECM->GetHDRBuffer());
	Ref<Shader> shader = view.get<Ref<Shader>>(gECM->GetHDRBuffer());

	RenderHDRPass(renderable, shader, buffer);
}

void Renderer::RenderRegularBuffer()
{
	entt::basic_view view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sRegularEntityQueue) {
		EntityType type = view.get<EntityType>(entity);
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		if (type == EntityType::REGULAR) {
			RenderRegularScene(renderable, transform, shader);
		}
	}
}

void Renderer::EndScene() {
	sDeferredEntityQueue.clear();
	sRegularEntityQueue.clear();
}

void Renderer::RenderDeferredScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	entt::basic_view view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sDeferredEntityQueue) {
		EntityType type = view.get<EntityType>(entity);
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		if (type == EntityType::DEFERRED_GEOMETRY) {
			RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
		}
		else if (type == EntityType::SKYBOX) {
			RenderSkybox(renderable, transform, shader);
		}
		else if (type == EntityType::AXIS) {
			RenderAxis(renderable, transform, shader);
		}
	}
}

void Renderer::RenderRegularScene(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	entt::basic_view view = gECM->GetRegistry().view<EntityType, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sRegularEntityQueue) {
		EntityType type = view.get<EntityType>(entity);
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		if (type == EntityType::REGULAR) {
			RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
		}
	}
}

void Renderer::RenderSkybox(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	shader->Use();

	glm::vec3 position;
	position = sCamera->GetPosition();
	transform->SetPosition(position);

	glm::mat4 model = transform->GetModelTransform();
	glm::mat4 view = sCamera->GetViewMatrix();
	glm::mat4 projection = sCamera->GetProjectionMatrix();
	

	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);

	shader->UnUse();
}

void Renderer::RenderAxis(Ref<Renderable> renderable, Ref<Transform> transform, Ref<Shader> shader) {
	shader->Use();

	glm::vec3 pos, forward;
	glm::mat4 projectionMat, viewMat, modelMat;

	pos = sCamera->GetPosition();
	forward = sCamera->GetForward();
	projectionMat = sCamera->GetOrthoProjectionMatrix();
	viewMat = sCamera->GetViewMatrix();

	transform->SetPosition(pos + (forward * glm::vec3(2.0)));
	transform->SetScale(glm::vec3(0.2f, 0.2f, 0.2f));
	modelMat = transform->GetModelTransform();

	shader->SetMat4("view", viewMat);
	shader->SetMat4("model", modelMat);
	shader->SetMat4("projection", projectionMat);

	RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);

	shader->UnUse();
}

void Renderer::RenderLightingPass(Ref<Renderable> renderable, Ref<Shader> shader) {
	shader->Use();

	glm::mat4 viewMat, projectionMat, modelMat;
	viewMat = sCamera->GetViewMatrix();
	projectionMat = sCamera->GetProjectionMatrix();
	modelMat = glm::mat4(1.0);

	shader->SetMat4("view", viewMat);
	shader->SetMat4("projection", projectionMat);
	shader->SetMat4("model", modelMat);

	RenderCommands::DrawIndexed(renderable, NULL, shader, sCamera);

	shader->UnUse();
}

void Renderer::RenderHDRPass(Ref<Renderable> renderable, Ref<Shader> shader, Ref<Texture> buffer) {
	shader->Use();

	shader->SetInt("hdrBuffer", 0);
	shader->SetFloat("exposure", gUserInterface->GetExposure());
	shader->SetFloat("gamma", gUserInterface->GetGamma());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, buffer->GetHandle());

	RenderCommands::DrawIndexed(renderable, NULL, shader, sCamera);

	shader->UnUse();
}