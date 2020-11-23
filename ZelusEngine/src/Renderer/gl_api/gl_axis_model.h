#pragma once

#include <glad/glad.h>

#include "gl_renderable.h"
#include "../../shader_manager.h"


extern ShaderManager* gShaderManager;

class AxisModel : public Renderable
{
private: 
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

	void Draw(const Ref<Camera> camera) override;
	void Update() override;
};

