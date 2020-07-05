#pragma once
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include "glad/glad.h"
#include "ref.h"
#include "log.h"
#include "camera.h"
#include "ui_input_handler.h"
#include "Renderer/renderer.h"
#include "Renderer/Entity.h"


extern Log* gLog;

class UserInterface
{
protected:
	GLFWwindow* window;
	const char* glslVersion = "#version 130";

	ImVec4 clearColour = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

	float exposure = 0.5;
	float gamma = 1.5;

	ImGuiIO *io;
	UserInterfaceInputHandler *ui_handler;

	Ref<Camera> camera;

	glm::vec3 eulerRot[3];

	float fov;

	bool exitPressed;
	bool gameWindowNoMove;
	bool gammaCorrection;

	bool logEnabled;
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
	void UpdatePropertiesWindow(std::vector<Ref<Entity>> entities);
	void UpdateLogWindow();


public:

	void StartUp();
	void ShutDown();
	void SetupGLFW();
	void SetupOpenGL();

	void Update(GLuint output, GLuint hdrOutput, GLuint gAlbedoOutput, GLuint gNormalOutput, GLuint gPositionOutput, std::vector<Ref<Entity>> entities);

	void Render();

	inline GLFWwindow* GetWindow() {
		return window;
	}

	inline Ref<Camera> GetCamera() {
		return camera;
	}

	inline glm::vec4 GetScreenClearColour() {
		return glm::vec4(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
	}

	inline float GetExposure() {
		return exposure;
	}

	inline float GetGamma() {
		return gamma;
	}
};