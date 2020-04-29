#pragma once
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include "camera.h"

class UserInterfaceInputHandler
{
private: 
	GLFWwindow* window;
	Camera* cam;

	bool mouseDown;
	bool mouseRelease;

	bool keyPress[512]; // Array to keep track of key presses. Keys use the glfw enum EG: GLFW_KEY_A

public:
	UserInterfaceInputHandler(GLFWwindow* window, Camera* cam);
	~UserInterfaceInputHandler();

	void EngineInputHandler();
};

