#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

class Transform
{
public: 
	Transform();
	~Transform();

	glm::mat4 GetModelTransform();
	
	void SetPosition(glm::vec3 position);
	void SetRototation(float angle, glm::vec3 axis);
	void SetScale(glm::vec3 scale);


private: 
	glm::vec3 mPositionVec;
	glm::fquat mRotationQuat;
	glm::vec3 mScaleVec;

	glm::mat4 mModel;
	glm::mat4 mRotationMat, mTranslationMat, mScaleMat;
};

