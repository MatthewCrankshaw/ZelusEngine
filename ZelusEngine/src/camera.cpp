#include "camera.h"

Camera::Camera() : InputHandler() {

	mViewAngleX = 0.0f; 
	mViewAngleY = 0.0f;

	mMovingForward = false;
	mMovingBackward = false;
	mMovingLeft = false;
	mMovingRight = false;
	mTrackMouse = false;
	mCursorPosition = glm::vec3(1.0);

	mMoveSpeed = glm::vec2(10.0f, 10.0f);
	mRotateSpeed = glm::vec2(0.2f, 0.2f);

	mCameraPosition = glm::vec3(0.0f, 0.0f, 0.0f); 
	mCameraPerspective = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000.0f);
	mCameraRotation = glm::fquat(1.0f, 0.0f, 0.0f, 0.0f);
}

void Camera::Update(double dt) {
	if (mMovingForward) {
		MoveForward(mMoveSpeed.x * (float)dt);
	}
	if (mMovingBackward) {
		MoveBackward(mMoveSpeed.x * (float)dt);
	}
	if (mMovingLeft) {
		MoveLeft(mMoveSpeed.y * (float)dt);
	}
	if (mMovingRight) {
		MoveRight(mMoveSpeed.y * (float)dt);
	}
#ifdef DEBUG_MODE
	std::cout << "Camera Position: " << glm::to_string(mCameraPosition) << " Camera Rotation: " << glm::to_string(mCameraRotation) << std::endl;
#endif

}

void Camera::MoveForward(float distance)
{
	glm::vec3 forward = glm::vec3(mCameraRotation * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mCameraPosition -= forward * distance;
}

void Camera::MoveBackward(float distance)
{
	glm::vec3 backward = glm::vec3(mCameraRotation * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f));
	mCameraPosition += backward * distance;
}

void Camera::MoveLeft(float distance)
{
	glm::vec3 left = glm::vec3(mCameraRotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	mCameraPosition -= (left * distance); 
}

void Camera::MoveRight(float distance)
{
	glm::vec3 right = glm::vec3(mCameraRotation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	mCameraPosition += (right * distance);
}

void Camera::Pitch(float angle)
{
	//Update the view angle X
	mViewAngleX += angle;

	//Make the bounds 180 degrees
	if (mViewAngleX < -glm::pi<float>() / 2.0f) {
		mViewAngleX = -glm::pi<float>() / 2.0f; 
	}else if (mViewAngleX > glm::pi<float>() / 2.0f) {
		mViewAngleX = glm::pi<float>() / 2.0f;
	}

	//Set the camera rotation
	mCameraRotation = glm::quat(cos(mViewAngleY / 2.0f), glm::vec3(0.0f, glm::sin(mViewAngleY / 2.0f), 0.0f)) * glm::quat(cos(mViewAngleX / 2.0f), glm::vec3(glm::sin(mViewAngleX / 2.0f), 0.0f, 0.0f));

}

void Camera::Yaw(float angle)
{
	//Update the view angle Y
	mViewAngleY += angle; 

	//Set the camera rotation
	mCameraRotation = glm::quat(cos(mViewAngleY / 2.0f), glm::vec3(0.0f, glm::sin(mViewAngleY / 2.0f), 0.0f)) * glm::quat(cos(mViewAngleX / 2.0f), glm::vec3(glm::sin(mViewAngleX / 2.0f), 0.0f, 0.0f));
}

void Camera::Roll(float angle)
{

}

void Camera::SetFieldOfView(float fov) {
	fieldOfView = fov;
}

void Camera::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) {
			mMovingForward = true;
		}
		else if (action == GLFW_RELEASE) {
			mMovingForward = false;
		}
	}
	else if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) {
			
			mMovingBackward = true;
		}
		else if (action == GLFW_RELEASE) {
			mMovingBackward = false;
		}
	}
	else if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) {
			mMovingLeft = true;
		}
		else if (action == GLFW_RELEASE) {
			mMovingLeft = false;
		}
	}
	else if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) {
			mMovingRight = true;
		}
		else if (action == GLFW_RELEASE) {
			mMovingRight = false;
		}
	}
}

void Camera::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if ((action == GLFW_PRESS)) {
			mTrackMouse = true;
		}
		else if (action == GLFW_RELEASE) {
			mTrackMouse = false;
		}
	}
}

void Camera::CursorPositionCallback(GLFWwindow* window, double x, double y){

	x = -x;
	y = -y;

	if (mCursorPosition.x == 0.0f && mCursorPosition.y == 0.0f) {
		mCursorPosition = mCursorPosition - glm::vec2(x, y);
		return;
	}
	if (mTrackMouse) {
		glm::vec2 d = glm::vec2(x, y);

		Pitch((d.y * 2.0f * glm::pi<float>() / (float)SCREEN_WIDTH) * mRotateSpeed.x);
		Yaw((d.x * 2.0f * glm::pi<float>() / (float)SCREEN_HEIGHT) * mRotateSpeed.y);

		if ((glm::length2(mCameraRotation) - 1.0f) > 0.00001) {
			mCameraRotation = glm::normalize(mCameraRotation);
		}
	}
	mCursorPosition = mCursorPosition - glm::vec2(x, y);
}

void Camera::FramebufferSizeCallback(GLFWwindow* window, int width, int height){
	mCameraPerspective = glm::perspective(glm::radians(fieldOfView), (float)width / (float)height, 0.1f, 100.0f);
}
