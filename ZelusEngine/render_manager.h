#pragma once

#include <vector>

#include "rectangle.h"
#include "sky_box.h"
#include "model.h"
#include "axis_model.h"

extern UserInterfaceManager* gUserInterface;

class RenderManager : public InputHandler
{
public: 

	void StartUp();

	void Render();

	void ShutDown();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)override;
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)override;
	void CursorPositionCallback(GLFWwindow* window, double x, double y)override;
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)override;

private:

	GLFWwindow* window;
	Camera* cam;

	const char* glsl_version = "#version 130";

	Renderable* m;
	Renderable* rect;
	Renderable* skyBox;
	Renderable* axis;

	
};

