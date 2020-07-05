#include "transform.h"
#include <iostream>

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
	mTranslationMat = glm::translate(glm::mat4(1.0f), mPositionVec);
	mRotationMat = glm::mat4_cast(mRotationQuat);
	mScaleMat = glm::scale(glm::mat4(1.0f), mScaleVec);

	mModel = mTranslationMat * mRotationMat * mScaleMat;

	return mModel;
}






