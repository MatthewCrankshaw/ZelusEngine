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

	GLuint finalFBO, finalTex, finalRBO;
	GLuint hdrFBO, hdrBuffer, hdrRBO;

	const char* glsl_version = "#version 130";

	Rectangle* m;
	Renderable* crysis;
	Renderable* skyBox;
	Renderable* axis;

	// Geometric buffer for differed shading
	GLuint mGeometricBuffer;
	// Texture IDs for goemetric data for differed shading
	GLuint mGeometricPosition, mGeometricNormal, mGeometricAlbedoSpecular;
	// Depth Buffer
	GLuint mRBODepth;

	//void RenderQuad();
	void RenderCube();
};

