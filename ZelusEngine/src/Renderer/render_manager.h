#pragma once

#include <vector>
#include <entt/entt.hpp>

#include "renderer.h"
#include "texture_factory/gl_texture_factory.h"
#include "renderable_factory/gl_renderable_factory.h"
#include "gl_api/renderables/gl_rectangle.h"
#include "gl_api/renderables/gl_cube.h"
#include "gl_api/renderables/gl_sky_box.h"
#include "gl_api/renderables/gl_model.h"
#include "gl_api/renderables/gl_axis_model.h"

extern UserInterface* gUserInterface;

class RenderManager
{
public: 
	void StartUp();
	void Render();
	void ShutDown();

private:

	Ref<Camera> camera;

	Ref<GLRenderableFactory> renderableFactory;
	Ref<GLTextureFactory> textureFactory;

	Ref<Texture> finalTex, hdrTex;

	GLuint finalFBO, finalRBO;
	GLuint hdrFBO, hdrRBO;

	// Geometric buffer for differed shading
	GLuint mGeometricBuffer;
	// GLTexture IDs for goemetric data for differed shading
	Ref<Texture> mGeometricPosition, mGeometricNormal, mGeometricAlbedoSpecular;
	// Depth Buffer
	GLuint mRBODepth;
};

