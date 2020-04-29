#pragma once
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include <glad/glad.h>

#include "camera.h"
#include "title_bar.h"
#include "ui_input_handler.h"

class UserInterface
{
protected:
	GLFWwindow* window;
	ImVec4 clearColour = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

	float lightPosition[3];
	float lightDirection[3];
	ImVec4 lightAmbient = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	ImVec4 lightDiffuse = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	ImVec4 lightSpecular = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	float lightConstant = 1.0f;
	float lightLinear = 0.7f;
	float lightQuadratic = 0.01f;
	float lightInnerCutOff = 25;
	float lightOuterCutOff = 35;


	ImVec4 materialAmbient = ImVec4(1.0f, 0.5f, 0.31f, 1.0f);
	ImVec4 materialDiffuse = ImVec4(1.0f, 0.5f, 0.31f, 1.0f);
	ImVec4 materialSpecular = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);


	float materialShininess = 14.0;

	ImGuiIO *io;
	UserInterfaceInputHandler *ui_handler;

	Camera* cam;

	TitleBar* titleBarUI;

	float fov;

	bool depthBufferEnabled;
	bool polyModeEnabled;
	bool cullFaceEnabled;
	bool gameWindowNoMove;
	bool gammaCorrection;

	void ToggleDeptTest();
	void TogglePolyMode();
	void ToggleCullFace();
	void ToggleGammaCorrection();


	void UpdateTitleWindow();
	void UpdateGameWindow(GLuint imageOutput);
	void UpdatePropertiesWindow();
	void UpdateLogWindow();

	std::string logStr;

public: 
	UserInterface();
	~UserInterface();

	void Init();
	void SetupGLFW(GLFWwindow* window);
	void SetupOpenGL(const char* glslVersion);
	void SetCamera(Camera* cam);

	void Update(GLuint output);
	void Render();

	ImVec4 GetScreenClearColour() {
		return clearColour;
	}

	glm::vec4 GetLightPosition() {
		return glm::vec4(lightPosition[0], lightPosition[1], lightPosition[2], 0.0f);
	}

	glm::vec4 GetLightDirection() {
		return glm::vec4(lightDirection[0], lightDirection[1], lightDirection[2], 0.0f);
	}

	glm::vec4 GetLightAmbient() {
		return glm::vec4(lightAmbient.x, lightAmbient.y, lightAmbient.z, lightAmbient.w);
	}

	glm::vec4 GetLightDiffuse() {
		return glm::vec4(lightDiffuse.x, lightDiffuse.y, lightDiffuse.z, lightDiffuse.w);
	}

	glm::vec4 GetLightSpecular() {
		return glm::vec4(lightSpecular.x, lightSpecular.y, lightSpecular.z, lightSpecular.w);
	}

	float GetLightConstant() {
		return lightConstant;
	}

	float GetLightLinear() {
		return lightLinear;
	}

	float GetLightQuadratic() {
		return lightQuadratic;
	}

	float GetLightInnerCutOff() {
		return lightInnerCutOff;
	}

	float GetLightOuterCutOff() {
		return lightOuterCutOff;
	}

	glm::vec4 GetMaterialAmbient() {
		return glm::vec4(materialAmbient.x, materialAmbient.y, materialAmbient.z, materialAmbient.w);
	}

	glm::vec4 GetMaterialDiffuse() {
		return glm::vec4(materialDiffuse.x, materialDiffuse.y, materialDiffuse.z, materialDiffuse.w);
	}

	glm::vec4 GetMaterialSpecular() {
		return glm::vec4(materialSpecular.x, materialSpecular.y, materialSpecular.z, materialSpecular.w);
	}

	float GetMaterialShininess() {
		return materialShininess;
	}
};