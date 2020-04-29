#include "renderable.h"

Renderable::Renderable(UserInterface *ui) {
	mTranslation = glm::mat4(1.0f);
	mRotation = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);
	mModelMat = glm::mat4(1.0f);

	mUi = ui;

	mShader = new Shader("Shaders/vertex.glsl", "Shaders/fragment.glsl");
}

void Renderable::setShader(Shader* shader)
{
	//TODO MEMORY LEAK IF mShader is not freed
	mShader = shader;
}

void Renderable::setPosition(const glm::vec3 position) {
	mTranslation = glm::translate(glm::mat4(1.0f), position);
}

void Renderable::translate(const glm::vec3 translate) {
	mTranslation = glm::translate(mTranslation, translate);
}