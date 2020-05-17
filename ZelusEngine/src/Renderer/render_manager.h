#pragma once

#include <vector>

#include "renderer.h"
#include "rectangle.h"
#include "sky_box.h"
#include "model.h"
#include "axis_model.h"

extern UserInterface* gUserInterface;

class RenderManager
{
public: 

	void StartUp();

	void Render();

	void ShutDown();

private:

	Camera* cam;

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

