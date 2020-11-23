#pragma once

#include <vector>
#include <entt/entt.hpp>

#include "renderer.h"
#include "entity_factory/gl_entity_factory.h"
#include "gl_api/gl_rectangle.h"
#include "gl_api/gl_cube.h"
#include "gl_api/gl_sky_box.h"
#include "gl_api/gl_model.h"
#include "gl_api/gl_axis_model.h"

extern UserInterface* gUserInterface;

class RenderManager
{
public: 
	void StartUp();
	void Render();
	void ShutDown();

private:

	Ref<Camera> camera;

	Ref<AbstractEntityFactory> entityFactory;

	GLuint finalFBO, finalTex, finalRBO;
	GLuint hdrFBO, hdrBuffer, hdrRBO;

	// Geometric buffer for differed shading
	GLuint mGeometricBuffer;
	// Texture IDs for goemetric data for differed shading
	GLuint mGeometricPosition, mGeometricNormal, mGeometricAlbedoSpecular;
	// Depth Buffer
	GLuint mRBODepth;
};

