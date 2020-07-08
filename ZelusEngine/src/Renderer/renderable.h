#pragma once
#include<glm/glm.hpp>

#include "../camera.h"

class Renderable
{
private:
	
protected:

	glm::mat4 mModelMat;

	glm::mat4 mTranslation;
	glm::mat4 mRotation;
	glm::mat4 mScale;

public:
	glm::vec3 mPosition;

public:
	Renderable();

	virtual void Draw(const Camera &camera) = 0;

	virtual void Update() = 0;

	void SetPosition(const glm::vec3 position);
	void PositionUpdate();
	void setScale(const glm::vec3 scale);
	void setRotation(float angle, glm::vec3 rot);

	inline void SetModelMat(glm::mat4 model){
		mModelMat = model;
	}

	void translate(const glm::vec3 translate);
};

