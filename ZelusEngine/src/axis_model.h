#pragma once

#include "renderable.h"
#include "glad/glad.h"
#include "shader_manager.h"


extern ShaderManager* gShaderManager;

class AxisModel : public Renderable
{
private: 
	GLuint mVAO; 
	GLuint mVBO;

	float mVertices[72] = {
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

public: 
	AxisModel();

	void Draw(const Camera& camera);

	void Update();
};
