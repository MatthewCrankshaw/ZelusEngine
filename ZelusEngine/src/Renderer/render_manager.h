#pragma once

#include <vector>

#include "renderer.h"
#include "gl_api/rectangle.h"
#include "gl_api/cube.h"
#include "gl_api/sky_box.h"
#include "gl_api/model.h"
#include "gl_api/axis_model.h"

extern UserInterface* gUserInterface;

class RenderManager
{
public: 

	void StartUp();

	void Render();

	void ShutDown();

private:

	Ref<Camera> camera;

	GLuint finalFBO, finalTex, finalRBO;
	GLuint hdrFBO, hdrBuffer, hdrRBO;

	// Geometric buffer for differed shading
	GLuint mGeometricBuffer;
	// Texture IDs for goemetric data for differed shading
	GLuint mGeometricPosition, mGeometricNormal, mGeometricAlbedoSpecular;
	// Depth Buffer
	GLuint mRBODepth;

	//void RenderQuad();
	void RenderCube();
};

