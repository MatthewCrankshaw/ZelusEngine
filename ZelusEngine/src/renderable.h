#pragma once
#include<glm/glm.hpp>

#include "camera.h"

class Renderable
{
private:
	
protected:
	glm::mat4 mModelMat;
	glm::mat4 mViewMat;
	glm::mat4 mProjectionMat;

	glm::mat4 mTranslation;
	glm::mat4 mRotation;
	glm::mat4 mScale;

public:
	Renderable();

	virtual void Draw(const Camera &camera) = 0;

	virtual void Update() = 0;

	void setPosition(const glm::vec3 position);
	void setScale(const glm::vec3 scale);
	void setRotation(float angle, glm::vec3 rot);
	void translate(const glm::vec3 translate);
};

