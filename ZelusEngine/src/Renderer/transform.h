#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

class Transform
{
public: 
	Transform();
	~Transform();

	glm::mat4 GetModelTransform();

	inline glm::vec3* GetVec3PositionPtr(){
		return &mPositionVec;
	}

	inline glm::vec3* GetVec3ScalePtr(){
		return &mScaleVec;
	}

	inline glm::fquat* GetFquatRotationPtr(){
		return &mRotationQuat;
	}

	inline void SetPosition(glm::vec3 position)
	{
		mPositionVec = position;
	}

	inline void SetRototation(float angle, glm::vec3 axis)
	{
		mRotationQuat = glm::angleAxis(angle, axis);
	}

	inline void SetRototation(glm::vec3 eulerAngle)
	{
		glm::fquat a = glm::angleAxis(eulerAngle.x, glm::vec3(1.0f, 0.0f, 0.0f));
		glm::fquat b = glm::angleAxis(eulerAngle.y, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::fquat c = glm::angleAxis(eulerAngle.z, glm::vec3(0.0f, 0.0f, 1.0f));

		mRotationQuat = a * b * c;
	}

	inline void SetScale(glm::vec3 scale)
	{
		mScaleVec = scale;
	}



private: 
	glm::vec3 mPositionVec;

	glm::fquat mRotationQuat;


	glm::vec3 mScaleVec;

	glm::mat4 mModel;
	glm::mat4 mRotationMat, mTranslationMat, mScaleMat;
};

