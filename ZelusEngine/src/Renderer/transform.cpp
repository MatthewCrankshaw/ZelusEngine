#include "transform.h"

Transform::Transform()
{
	mRotationQuat = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f); 
	mPositionVec = glm::vec3(0.0f, 0.0f, 0.0f);
	mScaleVec = glm::vec3(1.0f, 1.0f, 1.0f);


	mRotationMat = glm::mat4(1.0f);
	mTranslationMat = glm::mat4(1.0f); 
	mScaleMat = glm::mat4(1.0f);

	mModel = glm::mat4(1.0f);
}

Transform::~Transform(){

}

glm::mat4 Transform::GetModelTransform()
{
	mTranslationMat = glm::translate(mTranslationMat, mPositionVec);
	mRotationMat = glm::mat4_cast(mRotationQuat);
	mScaleMat = glm::scale(mScaleMat, mScaleVec);

	mModel = mScaleMat * mRotationMat * mTranslationMat;

	return mModel;
}

void Transform::SetPosition(glm::vec3 position)
{
	mPositionVec = position;
}

void Transform::SetRototation(float angle, glm::vec3 axis)
{
	mRotationQuat = glm::angleAxis(angle, axis);
}

void Transform::SetScale(glm::vec3 scale)
{
	mScaleVec = scale;
}







