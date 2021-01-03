#pragma once
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include "glad/glad.h"
#include "ref.h"
#include "entity_component_manager.h"
#include "log.h"
#include "camera.h"
#include "ui_input_handler.h"
#include "../meta_data.h"


extern Ref<Log> gLog;
extern Ref<EntityComponentManager> gECM;

class UserInterface
{
protected:
	GLFWwindow* mWindow;
	const char* mGlslVersion = "#version 130";

	ImVec4 mClearColour = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

	float mExposure = 0.5;
	float mGamma = 1.5;

	ImGuiIO *mIo;
	UserInterfaceInputHandler *mUiHandler;

	Ref<Camera> mCamera;

	float mFov;

	bool mOpen;
	bool mGameWindowNoMove;
	bool mGammaCorrection;

	bool mLogEnabled;
	bool mHDROutput;
	bool mGeometricAlbedoOutput;
	bool mGeometricNormalOutput;
	bool mGeometricPositionOutput;

	void ToggleBool(bool& value);


	void UpdateTitleWindow();
	void UpdateGameWindow(GLuint imageOutput);
	void UpdateHDRWindow(GLuint imageOutput);
	void UpdatePositionWindow(GLuint imageOutput);
	void UpdateAlbedoWindow(GLuint imageOutput);
	void UpdateNormalWindow(GLuint imageOutput);
	void UpdatePropertiesWindow();
	void UpdateLogWindow();
public:
	void StartUp();
	void ShutDown();
	void SetupGLFW();
	void SetupOpenGL();

	void Update(GLuint output, GLuint hdrOutput, GLuint gAlbedoOutput, GLuint gNormalOutput, GLuint gPositionOutput);

	void Render();

	inline GLFWwindow* GetWindow() {
		return mWindow;
	}

	inline Ref<Camera> GetCamera() {
		return mCamera;
	}

	inline glm::vec4 GetScreenClearColour() {
		return glm::vec4(mClearColour.x, mClearColour.y, mClearColour.z, mClearColour.w);
	}

	inline float GetExposure() {
		return mExposure;
	}

	inline float GetGamma() {
		return mGamma;
	}
};