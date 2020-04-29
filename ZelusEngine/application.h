#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "globals.h"
#include "shader.h"
#include "input_handler.h"
#include "texture.h"
#include "camera.h"
#include "user_interface.h"
#include "model.h"
#include "render_manager.h"
#include "sky_box.h"

//#define DEBUG_MODE;


class Application : public InputHandler
{
public: 
	Application();
	~Application();

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)override;
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)override;
	void CursorPositionCallback(GLFWwindow* window, double x, double y)override;
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)override;

private:
	GLFWwindow* window;
	//static int *screenWidth, *screenHeight;

	const char* glsl_version = "#version 130";
	UserInterface *ui;
	Camera *cam;

	Shader* defaultShader;
	Shader* lightShader;
	Shader* axisShader; 
	Shader* windowShader;
	Shader* skyboxShader;

	Texture* windowTexture;

	RenderManager* rm;

	Renderable* m;

	SkyBox* skyBox;

	float planeVertices[30] = {
		// positions          // texture Coords 
		 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

		 5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
		 5.0f, -0.5f, -5.0f,  1.0f, 1.0f
	};

	float axisVertices[72] = {
		0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,	0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,	 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,	 0.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f
	};

	GLuint planeVAO, planeVBO;
	GLuint axisVAO, axisVBO;

	void Init();
	void MainLoop();
	void Cleanup();
};

