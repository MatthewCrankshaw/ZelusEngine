#pragma once

#include "gl_renderable.h"
#include "../texture/gl_texture.h"
#include "../../shader.h"
#include "../../texture_factory/gl_texture_factory.h"
#include "../../../shader_manager.h"

extern Ref<ShaderManager> gShaderManager;

class GLRectangle : public GLRenderable
{
public:
	GLRectangle();

	void Draw(const Ref<Camera> camera) override;
	void Update() override;

private: 
	float mVertexData[32] = {
		// positions			// normal			// texture coords	
		 1.0f,  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,			// top right
		 1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,			// bottom right
		-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,			// bottom left
		-1.0f,  1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f			// top left 
	};
	unsigned int mIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};