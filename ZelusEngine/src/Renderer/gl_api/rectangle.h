#pragma once

#include "../renderable.h"
#include "../../shader.h"
#include "../../texture.h"
#include "../../shader_manager.h"

extern ShaderManager* gShaderManager;

class Rectangle : public Renderable
{
public:

	enum class ShaderModes { GEOMETRIC_PASS, LIGHTING_PASS, HDR_PASS, REGULAR };

	Rectangle();
	Rectangle(glm::vec3 colour);
	Rectangle(std::string textureFilname);

	void Draw(const Ref<Camera> camera);

	void Update();

	void SetShaderMode(ShaderModes mode) {
		mShaderMode = mode;
	}

private: 
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;

	bool mTexturedRect;
	GLuint mTextureId;

	glm::vec3 mColour;

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

