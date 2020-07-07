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

	inline glm::vec3* GetVec3RotationPtr(){
		return &mRotationVec;
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

	inline void SetScale(glm::vec3 scale)
	{
		mScaleVec = scale;
	}



private: 
	glm::vec3 mPositionVec = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 mRotationVec = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::fquat mRotationQuat = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);


	glm::vec3 mScaleVec = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 mModel = glm::mat4(1.0f);
	glm::mat4 mRotationMat = glm::mat4(1.0f); 
	glm::mat4 mTranslationMat = glm::mat4(1.0f); 
	glm::mat4 mScaleMat = glm::mat4(1.0f);
};

