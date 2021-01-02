#pragma once

#include "../texture/gl_texture.h"
#include "gl_renderable.h"
#include "../../shader.h"
#include "../../texture_factory/gl_texture_factory.h"
#include "../../../shader_manager.h"

extern Ref<ShaderManager> gShaderManager;

class GLRectangle : public GLRenderable
{
public:

	enum class ShaderModes { GEOMETRIC_PASS, DEFERRED_LIGHTING, HDR_PASS, REGULAR };

	GLRectangle();
	GLRectangle(glm::vec3 colour);
	GLRectangle(std::string textureFilname);

	void Draw(const Ref<Camera> camera) override;
	void Update() override;

	void SetShaderMode(ShaderModes mode) {
		mShaderMode = mode;
	}

private: 
	bool mTexturedRect;
	GLuint mTextureId;

	glm::vec3 mColour;
	glm::mat4 mModelMat;

	ShaderModes mShaderMode;

	float mVertexData[32] = {
		// positions			// texture coords	// normal		
		 1.0f,  1.0f, 0.0f,		1.0f, 1.0f,			0.0f, 1.0f, 0.0f,// top right
		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f,			0.0f, 1.0f, 0.0f,// bottom right
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,			0.0f, 1.0f, 0.0f,// bottom left
		-1.0f,  1.0f, 0.0f,		0.0f, 1.0f,			0.0f, 1.0f, 0.0f,// top left 
	};
	unsigned int mIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};

