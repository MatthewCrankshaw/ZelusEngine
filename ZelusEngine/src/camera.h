#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "input_handler.h"
#include "globals.h"

class Camera : public InputHandler
{
public:
	Camera();

	void Update(double dt);

	void MoveForward(float distance);
	void MoveBackward(float distance); 
	void MoveLeft(float distance); 
	void MoveRight(float distance); 

	void Pitch(float angle); 
	void Yaw(float angle);
	void Roll(float angle); 

	void GetViewMatrix(glm::mat4& view) const {
		glm::vec3 forward = glm::vec3(mCameraRotation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f));
		glm::vec3 up = glm::vec3(mCameraRotation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
		view = glm::lookAt(mCameraPosition, mCameraPosition + forward, up);
	}

	void GetProjectionMatrix(glm::mat4& projection) const {
		projection = glm::perspective(glm::radians(fieldOfView), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	}

	void GetOrthoProjectionMatrix(glm::mat4& projection) const {
		projection = glm::ortho(-1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 1000.0f);
	}

	void GetPosition(glm::vec3& pos) const{
		pos = mCameraPosition;
	}

	void GetForward(glm::vec3& forward) const {
		forward = mCameraRotation * glm::vec3(0.0f, 0.0f, -1.0f);
	}

	void GetRotation(glm::fquat& rot)const {
		rot = mCameraRotation;
	}


	void SetFieldOfView(float fov);

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override; 
	void CursorPositionCallback(GLFWwindow* window, double x, double y) override; 
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height) override;
	

private: 
	float mViewAngleX, mViewAngleY;
	bool mMovingForward, mMovingBackward, mMovingLeft, mMovingRight, mTrackMouse;

	float fieldOfView = 45.0f;

	glm::vec2 mMoveSpeed, mRotateSpeed;

	glm::mat4 mCameraPerspective;

	glm::fquat mCameraRotation;
	glm::vec3 mCameraPosition;

	glm::vec2 mCursorPosition;


};

