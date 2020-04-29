#pragma once
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_glfw.h>
#include <ImGui\imgui_impl_opengl3.h>

#include <iostream>
#include "globals.h"

class TitleBar
{
private: 
	GLFWwindow* window;

	bool fullscreen;
	bool exitPressed;

public:
	TitleBar();

	void SetupGLFW(GLFWwindow* window);
	void CreateTitleBar();
	void Update();
};

