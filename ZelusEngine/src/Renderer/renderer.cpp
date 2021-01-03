#include "renderer.h"

Ref<Camera> Renderer::sCamera = nullptr;
std::vector<entt::entity> Renderer::sDeferredEntityQueue;
std::vector<entt::entity> Renderer::sRegularEntityQueue;

void Renderer::BeginScene(Ref<Camera> camera) {
	sCamera = camera;
	entt::basic_view view = gECM->GetRegistry().view<Ref<MetaData>, Ref<Renderable>, Ref<Shader>>();

	for (auto entity : view) {
		EntityType type = view.get<Ref<MetaData>>(entity)->GetType();
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
	entt::basic_view view = gECM->GetRegistry().view<Ref<MetaData>, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sDeferredEntityQueue) {
		EntityType type = view.get<Ref<MetaData>>(entity)->GetType();
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		if (type == EntityType::DEFERRED_GEOMETRY) {
			glm::mat4 model = transform->GetModelTransform();
			glm::mat4 view = sCamera->GetViewMatrix();
			glm::mat4 projection = sCamera->GetProjectionMatrix();

			shader->SetMat4("model", model);
			shader->SetMat4("view", view);
			shader->SetMat4("projection", projection);
			shader->SetBool("textured", 0);
			if (gECM->HasTexture(entity)) {
				RenderCommands::SetTexture(shader, gECM->GetTexture(entity));
				shader->SetBool("textured", 1);
			}
			RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
		}
		else if (type == EntityType::SKYBOX) {
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
		}
		else if (type == EntityType::AXIS) {
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
		}
	}
}

void Renderer::RenderDeferredLightingBuffer()
{
	auto view = gECM->GetRegistry().view<Ref<MetaData>, Ref<Renderable>, Ref<Shader>>();

	EntityType type = view.get<Ref<MetaData>>(gECM->GetLightingBuffer())->GetType();
	Ref<Renderable> renderable = view.get<Ref<Renderable>>(gECM->GetLightingBuffer());
	Ref<Shader> shader = view.get<Ref<Shader>>(gECM->GetLightingBuffer());

	glm::mat4 viewMat, projectionMat, modelMat;
	viewMat = sCamera->GetViewMatrix();
	projectionMat = sCamera->GetProjectionMatrix();
	modelMat = glm::mat4(1.0);

	shader->SetMat4("view", viewMat);
	shader->SetMat4("projection", projectionMat);
	shader->SetMat4("model", modelMat);

	RenderCommands::DrawIndexed(renderable, NULL, shader, sCamera);
}

void Renderer::RenderHDRBuffer()
{
	auto view = gECM->GetRegistry().view<Ref<MetaData>, Ref<Renderable>, Ref<Shader>, Ref<Texture>>();
	auto entity = gECM->GetHDRBuffer();

	EntityType type = view.get<Ref<MetaData>>(entity)->GetType();
	Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
	Ref<Shader> shader = view.get<Ref<Shader>>(entity);
	Ref<Texture> texture = view.get<Ref<Texture>>(entity);

	shader->SetInt("hdrBuffer", 0);
	shader->SetFloat("exposure", gUserInterface->GetExposure());
	shader->SetFloat("gamma", gUserInterface->GetGamma());
	RenderCommands::SetTexture(shader, texture);
	RenderCommands::DrawIndexed(renderable, NULL, shader, sCamera);
}

void Renderer::RenderRegularBuffer()
{
	entt::basic_view view = gECM->GetRegistry().view<Ref<MetaData>, Ref<Renderable>, Ref<Transform>, Ref<Shader>>();

	for (auto entity : sRegularEntityQueue) {
		EntityType type = view.get<Ref<MetaData>>(entity)->GetType();
		Ref<Renderable> renderable = view.get<Ref<Renderable>>(entity);
		Ref<Transform> transform = view.get<Ref<Transform>>(entity);
		Ref<Shader> shader = view.get<Ref<Shader>>(entity);

		if (type == EntityType::REGULAR) {
			glm::mat4 model = transform->GetModelTransform();
			glm::mat4 view = sCamera->GetViewMatrix();
			glm::mat4 projection = sCamera->GetProjectionMatrix();

			shader->SetMat4("model", model);
			shader->SetMat4("view", view);
			shader->SetMat4("projection", projection);
			shader->SetBool("textured", 0);
			if (gECM->HasTexture(entity)) {
				RenderCommands::SetTexture(shader, gECM->GetTexture(entity));
				shader->SetBool("textured", 1);
			}

			RenderCommands::DrawIndexed(renderable, transform, shader, sCamera);
		}
	}
}

void Renderer::EndScene() {
	sDeferredEntityQueue.clear();
	sRegularEntityQueue.clear();
}

