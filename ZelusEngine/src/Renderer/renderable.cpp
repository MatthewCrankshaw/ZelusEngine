#include "renderable.h"

Renderable::Renderable() {
	mTranslation = glm::mat4(1.0f);
	mRotation = glm::mat4(1.0f);
	mScale = glm::mat4(1.0f);
	mModelMat = glm::mat4(1.0f);
}

void Renderable::setPosition(const glm::vec3 position) {
	mTranslation = glm::translate(glm::mat4(1.0f), position);
}

void Renderable::setScale(const glm::vec3 scale)
{
	mScale = glm::scale(glm::mat4(1.0), scale);
}

void Renderable::setRotation(float angle, const glm::vec3 rot) {
	glm::fquat rotation = glm::angleAxis(glm::radians(angle), rot);
	mRotation = glm::toMat4(rotation);
}

void Renderable::translate(const glm::vec3 translate) {
	mTranslation = glm::translate(mTranslation, translate);
}