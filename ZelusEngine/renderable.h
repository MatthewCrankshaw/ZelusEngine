#pragma once
#include<glm/glm.hpp>

#include "shader.h"
#include "camera.h"
#include "user_interface.h"

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

	Shader* mShader;

	UserInterface* mUi;
public:
	Renderable(UserInterface* ui);

	virtual void Draw(const Camera &camera) = 0;

	virtual void Update() = 0;

	void setShader(Shader* shader);
	void setPosition(const glm::vec3 position);
	void translate(const glm::vec3 translate);
};

