#pragma once

#include "renderable.h"
#include "shader.h"
#include "texture.h"

class Rectangle : public Renderable
{
private: 
	GLuint mVAO;
	GLuint mVBO;
	GLuint mEBO;

	bool mTexturedRect;
	GLuint mTextureId;

	glm::vec3 mColour;

	Shader* mShader;

	float mVertexData[20] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // top left 
	};
	unsigned int mIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

public: 

	Rectangle();
	Rectangle(glm::vec3 colour);
	Rectangle(std::string textureFilname);

	void Draw(const Camera& camera);

	void Update();
};

